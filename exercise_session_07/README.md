### Analysis of C/C++ Pointer and Array Behavior

We assume the array is initialized as follows: `int p[10] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};`


|

**Question**

 |

**Answer**


 |
|

**a. What C/C++ type is `p`?**

 |

`int [10]` (Array of 10 integers)


 |
|

**b. What is the type of `*p`?**

 |

`int`


 |
|

**c. What is the type of `&p`?**

 |

`int (*)[10]` (Pointer to an array of 10 integers)


 |


|

**Question**

 |

**Value/Meaning**


 |
|

**d. What is the value of `*p`?**

 |

`10`

 |
|

**e. What is the value of `p[0]`?**

 |

`10`

 |
|

**f. What is the value of `p[3]`?**

 |

`40`


 |
|

**g. What is the value of `*(p+5)`?**

 |

`60`


 |
|

**h. What is the value of `*p+5`?**

 |

`15`


 |
|

**i. What does `p[-1] = 42` mean in C/C++?**

 |

**Undefined Behavior (UB)**


 |
|

**j. Let: `int *q = p-1;`. What is the value of `q[0]`?**

 |

**Undefined Behavior (UB)**


 |
|

**k. What is the value of `*(q+10)`?**

 |

`100`


 |
|

**l. What is the value of `*(q+11)`?**

 |

**Undefined Behavior (UB)**


 |




### Exercise 2: C++ Dynamic Array Pointer Analysis

The analysis below is based on the following C++ initialization:

```
int ** M = new int *[2];
M [0] = new int [5]{0 ,1 ,2 ,3 ,4};
M [1] = new int [5]{5 ,6 ,7 ,8 ,9};

```

#### a. What data type is M?

`M` is an **`int**` (pointer to a pointer to an integer).

It points to an array of two `int*` (pointers to integer), where each `int*` points to a row of the data.

#### b. What are M, *M, **M?

|

**Expression**

 |

**Type**

 |

**Value/Meaning**

 |
|

**`M`**

 |

`int**`

 |

The **address** of the first pointer (the address of `M[0]`).

 |
|

**`*M`**

 |

`int*`

 |

The **value** at `M` (the address of `M[0]`), which is the base address of the first row (the address of the value `0`).

 |
|

**`**M`**

 |

`int`

 |

The **value** at the address held by `*M`, which is the first element of the first row (`M[0][0]`), which is **`0`**.

 |

#### c. What is M[1][3], *(M[0]+1), *(*(M+1)+3)?

|

**Expression**

 |

**Equivalent Notation**

 |

**Value**

 |
|

**`M[1][3]`**

 |

N/A

 |

**`8`**

 |
|

**`*(M[0]+1)`**

 |

`M[0][1]`

 |

**`1`**

 |
|

**`*(*(M+1)+3)`**

 |

`M[1][3]`

 |

**`8`**

 |

#### d. Are the M[0] and M[1] arrays stored next to each other in the memory? In other words, is it true that *(M[0]+5)==M[1][0]?

**No, this is generally false.**

1.  **Non-Contiguous Allocation:** The statements `M[0] = new int[5]` and `M[1] = new int[5]` execute separate dynamic memory allocation calls. The operating system places these two blocks of 5 integers in independent locations on the heap.

2.  **Undefined Behavior (UB):** The expression `*(M[0]+5)` attempts to read the memory location 5 integers past the end of the `M[0]` block. Since that location is not guaranteed to be the start of `M[1]`, this access results in **Undefined Behavior**.




### Exercise 3: Array Strides Analysis

**Dimensions:**

-   Rows (y-dimension): $R = 6$ (indices $0$ to $5$)

-   Columns (x-dimension): $C = 14$ (indices $0$ to $13$)

#### a. Which variable ($x$ or $y$) tells you which row it is, and which tells you the column?

-   $y$ tells you the **row** index (ranging from $0$ to $5$).

-   $x$ tells you the **column** index (ranging from $0$ to $13$).

#### b. How many total elements are in the table?

Total elements = Rows $\times$ Columns $= 6 \times 14 = 84$ elements.

#### c. Are the elements $(1,3)$ and $(1,4)$ adjacent in memory, or is it rather $(1,3)$ and $(2,3)$?

-   Elements in the **same row** are adjacent in memory.

-   The pair $(1,3)$** and **$(1,4)$ are in the same row ($y=1$) and are adjacent columns, meaning they **are adjacent in memory**.

-   The pair $(1,3)$ and $(2,3)$ are separated by an entire row's worth of elements ($14$ elements).

#### d. Is one of these choices "better"? Why or why not?

**No, neither choice is universally "better"; it depends on the language and how you iterate.**

-   **Row-Major (C/C++):** Elements in the same row are adjacent. This is best for code that iterates over rows first (e.g., `for(row) { for(col) }`).

-   **Column-Major (Fortran):** Elements in the same column are adjacent. This is best for code that iterates over columns first (e.g., `for(col) { for(row) }`).

The "better" choice is the one that matches the **access pattern** of your code to the **memory layout** of the array. Matching the two results in **spatial locality**, which maximizes cache hits and leads to much faster execution on modern CPUs.

#### e. From now on assume "row-major" order... What is the stride for the $x$ dimension?

In row-major order, elements in the same row are adjacent. Moving one step along the $x$ dimension (column) moves the memory address by the size of one element.

-   Stride for $x$ (column) dimension: $\mathbf{1}$ (element).

#### f. What is the stride of the $y$ dimension?

The $y$ dimension (row) stride is the distance you must jump in memory to get from $(x, y)$ to $(x, y+1)$, which is the length of one entire row.

-   Stride for $y$ (row) dimension: $\mathbf{14}$ (elements, the number of columns).

#### g. Where is element $(0,10)$?

In a flat, 1D array representation starting at $A[0]$, the element $(y, x)$ is found at the index $\text{Index} = y \times (\text{y-stride}) + x \times (\text{x-stride})$.

For $(0, 10)$:

$$\text{Index} = 0 \times 14 + 10 \times 1 = \mathbf{10}$$

The element is at $A[10]$.

#### h. Where is element $(3,0)$?

For $(3, 0)$:

$$\text{Index} = 3 \times 14 + 0 \times 1 = 42$$

The element is at $A[42]$.

#### i. Where is element $(4,7)$?

For $(4, 7)$:

$$\text{Index} = 4 \times 14 + 7 \times 1 = 56 + 7 = 63$$

The element is at $A[63]$.
