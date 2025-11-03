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
