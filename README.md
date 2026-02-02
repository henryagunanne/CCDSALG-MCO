# CCDSALG Major Course Output (MCO)

![Language](https://img.shields.io/badge/Language-C-blue)
![Course](https://img.shields.io/badge/Course-CCDSALG-green)
![Focus](https://img.shields.io/badge/Focus-Data%20Structures%20%26%20Algorithms-orange)
![Status](https://img.shields.io/badge/Status-Academic%20Project-lightgrey)

## 📌 Overview

This repository contains the **Major Course Output (MCO)** for the course **CCDSALG (Data Structures and Algorithms)**.  
The project demonstrates the practical application of **core algorithmic concepts**, emphasizing **correctness, efficiency, modular design, and performance analysis**.

The repository is divided into two major components:

- **MCO1:** Convex Hull computation using Graham’s Scan  
- **MCO2:** Graph algorithms and traversal techniques  

Both implementations were developed in **C**, following strict academic constraints and best practices in algorithm design.

---

## 🧠 Learning Objectives

- Apply **abstract data structures** (stacks, graphs) to real computational problems  
- Implement and compare **slow vs fast algorithms**  
- Analyze **time complexity and empirical performance**  
- Practice **modular programming** using header and source files  
- Strengthen understanding of **algorithm correctness and optimization**

---

## 📐 MCO1 — Convex Hull (Graham’s Scan)

### 🔍 Problem Description
Compute the **convex hull** of a set of 2D points using **Graham’s Scan algorithm**, a classic computational geometry technique.

### 🛠 Key Concepts Applied
- Stack Data Structure
- Sorting Algorithms (Slow vs Fast)
- Polar Angle Computation
- Computational Geometry
- Time Complexity Measurement

### 📋 Features
- Custom stack implementation supporting up to **32,768 points**
- Two sorting strategies:
  - **Slow:** Quadratic-time algorithm (e.g., Selection / Insertion Sort)
  - **Fast:** O(n log n) algorithm (e.g., Quick Sort / Merge Sort)
- Two Graham Scan implementations:
  - Version 1: Uses slow sorting
  - Version 2: Uses fast sorting
- Elapsed execution time measured in **milliseconds**
- Outputs hull points in **counterclockwise order**, formatted to **6 decimal places**

### 📂 Output
- Convex hull points written to a text file
- Performance comparison between algorithm versions

---

## 🌐 MCO2 — Graph Algorithms

### 🔍 Problem Description
Implementation of **graph-based algorithms** focusing on traversal, connectivity, and structured graph processing.

### 🛠 Key Concepts Applied
- Graph representations (Adjacency structures)
- Traversal algorithms (e.g., DFS, BFS)
- Algorithm correctness and efficiency
- Modular C programming

### 📋 Features
- Clean separation of graph logic and driver programs
- Handles multiple test cases
- Designed for scalability and clarity
- Emphasizes algorithmic reasoning over library usage

---

### ▶️ How to Compile and Run

Compile (Example for GCC)
```bat
gcc main.c stack.c sort.c graham_scan.c -o program
```

Run
```bash
./program
```

> Input and output file names are prompted at runtime.

---

### 📊 Performance Analysis

For MCO1, extensive testing was conducted using input sizes from
2⁶ (64 points) up to 2¹⁵ (32,768 points).

Results show:
- Significant performance improvement when using O(n log n) sorting
- Expected growth behavior consistent with algorithmic complexity theory

--- 

### 🎓 Academic Integrity

This project strictly follows the academic honesty policy:
No external algorithm implementations were copied
All logic was implemented from scratch
External references were used for learning only, not direct reuse

---

## 🤖 AI Assistance Disclosure

This project and its source code were developed entirely by the authors.  
AI tools (including ChatGPT) were used **solely as a writing and documentation aid**, primarily to help with:

- README structuring and formatting
- Clarifying technical descriptions
- Improving documentation clarity and presentation

All algorithms, data structures, system design decisions, and source code implementations were **independently designed and written by the authors** in compliance with course policies on academic honesty.

No AI-generated code was used in the implementation of the project.
