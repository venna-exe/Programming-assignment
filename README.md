# Programming-assignment : C++ Habit Tracker

A console habit tracker written in C++ for our programming course (Group 8). The idea behind it is that a reminder is easy to ignore, so skipping a habit should cost the user something. In this program, the cost is a written reflection.

## What it does

The program has a small menu where you can add habits and view them. A habit can be set up in two ways. A time-based habit is tied to an hour of the day. A habit-based habit comes after another habit that already exists, for example drinking water after waking up. The first habit you ever add is always time-based, because there is nothing to attach it to yet.

Habits that belong to the same routine can be put in a group with a title. When you add a habit after a prerequisite, you can either create a new group or reuse the group the prerequisite is already in. The habit list shows each habit with its time or prerequisite and its group.

All habits are saved to `habits.txt`, so they are still there the next time you open the program.

## Penalty system

Every time the program starts, it checks each habit's last-done date. If a habit has gone two or more days without being done, the program stops before the menu and asks for a reflection. The reflection should answer three questions:

1. Why did you forget to do this habit?
2. What prevented you from doing it?
3. What concrete action will you take so it happens less?

The reflection has to be at least 100 words. If it is shorter, the program says how many words were counted and asks again. Once it is long enough, it is saved to `reflections.txt` along with the habit name, the streak is set back to zero, and the program moves on to the menu.

## How to run

You need a C++ compiler such as g++.

```
g++ main.cpp -o habit_tracker
./habit_tracker
```

On Windows, run `habit_tracker.exe` instead.

Run it from the folder where you want the data kept. `habits.txt` and `reflections.txt` are created next to the program. To start from scratch, close the program and delete them.

## Menu

```
1. Add habit
2. View habits
0. Exit
```

## Data files

`habits.txt` stores four lines per habit: the name, the type and hour, the prerequisite, and the group. `reflections.txt` stores the habit name followed by the reflection text.

## Notes

- Days are counted using UTC+7 (Western Indonesia Time), so a new day starts at local midnight in Yogyakarta.
- The program holds up to 100 habits.
- It only uses basic C++: structs, arrays, loops, conditionals, and file input and output.

## Files in this repo

- `main.cpp`: the program
- `Habit Tracker Proposal.pdf`: project proposal
- `Habit Tracking PPT.pdf`: presentation slides
- `flowchart vertikal.png`: flowchart of the add-habit process

## Group 8
1. Hudzaifah
2. M Abiyakhsa T 
3. Christian Kayden K

