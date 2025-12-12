# HPC2025 Exercise Sheet 13: MapReduce Solution

## Exercise 2: Map & Reduce Answers

The MapReduce job was executed successfully using the Hadoop Streaming utility with Python 2.

### Question 1: How many map and reduction operations were performed? How many lines/entries were treated?

The final counter values were determined by checking HDFS file line counts:

| Metric | Value |
| :--- | :--- |
| **Launched Map Tasks** | **12** (One for each input split) |
| **Launched Reduce Tasks** | **1** (Default configuration) |
| **Map Input Records (Lines Treated)** | **35,505** |
| **Reduce Output Records (Unique Words)** | **47,090** |

### Question 2: Which output folder(s)/file(s) were created?

The output folder created on HDFS is `/output`. The result files are `/output/part-00000` (word counts) and `/output/_SUCCESS`.

### Question 3: Find the file containing the information about the word counts and have a look on the results of map&reduce operation.

The file containing the word counts is `/output/part-00000`. The contents of this file are included in this repository as `exercise13_output.txt`.

### Question 4: Visit the hadoop api from your local machine. Can you find the output files?

Yes. The output is accessible via the SSH port forwarding setup, specifically through the HDFS NameNode UI (`http://localhost:8088`).
