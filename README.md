# WonderTechs_SDG3_StudyWell

StudyWell is a lightweight, terminal-based application built in C++. Inspired by UN Sustainable Development Goal 3 (Good Health and Well-Being), it helps students track their mental wellness, log study sessions, and receive research-backed, data-driven study plans to prevent burnout.

---

The Developers (Team WonderTechs)
Capablanca, Dimple Ann Mae S.
Del Prado, Jade Louis S.
Florendo, Allysa Anne D.
Villena, Aiden Johann K.

---

Key Features
- User login system
- Wellness Monitoring / Checking:
      - A 10-question quiz that scores Joy of Learning (JL), Academic Efficacy (AE), Time Management (TM), and Perceived Stress (PS).
- Smart Study Plan Provider: 
      - Dynamically recommends study habits and time limits based on your wellness scores.
- Full Session History (Create, Read, Update, Delete):
      - Allows users to view history with real-time running averages, edit logs via specialized markers, and delete target sessions.
- Study session and Wellness check session tracking 
- File handling using “data.txt” file (text database):
      -Automatically saves and syncs all user sessions in `data.txt` across application restarts.
Input validation:
      - Uses `std::cin.fail()` to completely prevent crashes and infinite loops caused by invalid inputs (like entering letters instead of numbers).
---

Setup and Installation

System Requirements
- Windows 10/11
- VS Code or any C++ IDE
- g++ compiler

Setup Instructions
1. Download or clone the repository.
2. Open the project folder in VS Code.
3. Make sure all `.cpp` and `.h` files are inside the `CODE` folder.
4. Compile the program using g++.

Compilation & Execution Steps 
1. Open your terminal or command prompt inside the project folder. 
2. Compile the multi-file project using this command: 
-```bash g++ main.cpp StudyWell.cpp -o StudyWell 
