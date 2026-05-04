Power Quality Waveform Analyser

How to compile and run in CLion:

1. open project folder using CLion
2. make sure that "power_quality_log.csv" is in the project folder
3. Edit the run configuration to ensure that you add "power_quality_log.csv" into program arguments
4. Run the program

How to compile and run using GCC

1. Open a terminal in the project folder
2. compile with: gcc main.c io.c waveform.c -o power_quality_analyser -lm
3. Run with: ./power_quality_analyser power_quality_log.csv

If using windows then run with: power_quality_analyser.exe power_quality_log.csv


GitHub repository link:
https://github.com/LinkaLTU/PowerQualityAnalyser