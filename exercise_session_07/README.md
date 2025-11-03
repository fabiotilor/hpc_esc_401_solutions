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

