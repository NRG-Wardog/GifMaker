# Magshimim First Year - Final Project (C)

## Introduction

This repository contains my **final project** for the **Magshimim First Year** program, implemented in **C**. The project is a simple **GIF Maker**, allowing users to create and manage animated sequences by adding, removing, and modifying frames.

## Project Structure

The repository consists of:

- **Source Code**: Implementation of the project logic in multiple C source files.
- **Header Files**: Function and structure declarations for better modularity.
- **Documentation**: Explanation of the approach, logic, and methodology used in the solution.
- **Test Cases**: Sample input and output cases to validate correctness.

## Technologies Used

- **Programming Language**: C
- **Development Environment**: Visual Studio Code / GCC / Clang / Any other IDE used
- **Version Control**: Git
- **Libraries**: OpenCV (for displaying frames)

## Features

- Add and remove frames from the GIF sequence.
- Modify frame duration and order.
- Save and load GIF projects.
- Display animated sequences using OpenCV.

## How to Run

The execution of the program depends on whether it requires parameters or not:

- **Compile the Project**:
  ```sh
  gcc -o gif_maker prog.c linkedList.c openAndEditProg.c view.c -lopencv_core -lopencv_highgui -lopencv_imgcodecs
  ```

- **Run the Program**:
  ```sh
  ./gif_maker
  ```

## Example Test Case

### Input:
```
Add a new frame with path "image1.jpg" and duration 500ms
Save project
Play movie
```

### Output:
```
Frame added successfully!
Project saved.
Displaying animation...
```

## Future Improvements

- Improve efficiency using advanced data structures.
- Add more edge case testing.
- Implement GUI or visualization for better user experience.

## Contact

For any questions or discussions, feel free to reach out! **If you are a Magshimim student, do not copy! Doing so is strictly prohibited and may result in disciplinary actions.**

---
📌 **Note**: This project is part of my learning process in **Magshimim First Year** and represents my growth in programming and problem-solving.

## License

### **Copyright © [Your Name / Organization]**

This project is licensed under the **Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International (CC BY-NC-ND 4.0)**.

You are **not** allowed to:
- Copy, modify, or distribute this work without explicit permission.
- Use this work for commercial purposes.
- Claim ownership or credit for this work.

### **Permitted Usage**
You may view the code and learn from it, but you **may not copy or submit it as your own work.**

### **Strictly Prohibited for Magshimim Students**
Magshimim students are explicitly **forbidden** from copying, sharing, or using this code in their submissions. Violations may result in academic consequences.

For more details, see the full license at: [License](LICENSE)

