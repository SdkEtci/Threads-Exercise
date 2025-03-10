# Threads Exercise

## Description
This project is designed to analyze a log file and count occurrences of different log types such as "ERROR", "WARNING", and "INFO" using multithreading in C. The application reads the log file line by line instead of loading it entirely into memory, making it efficient for handling large log files.

## Features
- Multi-threaded log analysis using pthreads
- Counts occurrences of "ERROR", "WARNING", and "INFO"
- Uses system cores efficiently (number of threads = total cores - 1)
- Synchronization with mutex to handle shared variables
- Comparison of single-threaded and multi-threaded performance

## Prerequisites
- GCC compiler installed
- A Linux or macOS system (or Windows with WSL)
- Basic knowledge of C and pthreads

## Installation & Usage
1. Clone the repository:
   ```sh
   git clone https://github.com/SdkEtci/Threads-Exercise.git
   ```
2. Navigate to the project directory:
   ```sh
   cd Threads-Exercise
   ```
3. Compile the C program:
   ```sh
   gcc -o log_analyzer log_analyzer.c -pthread
   ```
4. Run the program:
   ```sh
   ./log_analyzer log_file.txt
   ```

## Output Example
```
ERROR : 68
WARNING : 105
INFO : 745
```

## Contribution
Feel free to fork this repository and submit pull requests with improvements or additional features.


