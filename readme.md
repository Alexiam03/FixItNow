# FixItNow

A C++ console application for managing the activity of a home-appliance repair shop. It handles the employee database, the catalog of repairable appliances, and the processing of repair requests through a time-based workflow simulation.

The project is built around object-oriented design: class hierarchies, virtual functions and polymorphism, operator overloading, input validation and exception handling.

## Features

- **Employee management:** add, modify, delete and list employees of three types (technician, receptionist, supervisor). Each type has its own salary calculation.
- **Appliance catalog:** refrigerators, TVs and washing machines, with brand, model, manufacturing year and catalog price.
- **Repair requests:** requests are loaded from files, validated, and given a complexity, duration and price computed automatically.
- **Workflow simulation:** time advances step by step, available technicians are assigned to waiting requests, and ongoing repairs are completed.
- **Reports (CSV):**
  - top 3 employees by salary (`raport_top_3.csv`)
  - the technician with the longest repair duration (`raport_tehnician.csv`)
  - pending requests grouped by appliance type, brand and model, in alphabetical order (`raport_cereri.csv`)
  
  The repository includes example output for all three reports (`raport_top_3.csv`, `raport_tehnician.csv`, `raport_cereri.csv`).
- **Input validation:** CNP validation according to the official specification, and calendar date checks (leap years, days per month).

> The service only works if it has at least 3 technicians, 1 receptionist and 1 supervisor.

## Class overview

### Helper classes

| Class | Role |
|-------|------|
| `date` | A calendar date (day, month, year), with validation for leap years and the number of days in each month. |
| `dateTime` | Extends `date` with time (hour, minute, second). Used to order repair requests chronologically (`operator<` is implemented). |

### Employees

`echipa_service` is the base class. It stores the common data (ID, name, CNP, hire date), validates the CNP, exposes getters, and declares a virtual display function plus a friend output operator. Salary is computed polymorphically, so each employee type has its own formula.

| Class | Description |
|-------|-------------|
| `tehnician` | Keeps a list of appliance types it can repair and the total value of the repairs it has completed. Can add a specialization, check whether it can repair a given appliance, and compute its own salary. |
| `receptioner` | Keeps the list of IDs of the requests it has registered. |
| `supervizor` | Overrides only the salary calculation. |

### Appliances

`electrocasnic` is the base class. It stores brand, model, catalog price and manufacturing year, with getters, a virtual display function and an output operator.

| Class | Extra data |
|-------|------------|
| `frigider` | Whether it has a freezer (`bool`). |
| `televizor` | Screen diagonal in cm (`double`). |
| `masina_de_spalat` | Capacity in kg (`double`). |

Each derived class overrides the display function and provides a getter for its own attribute.

### Application core

| Class | Description |
|-------|-------------|
| `cerere_reparatie` | A service ticket: ID, appliance type, brand and model, submission timestamp, repair complexity, duration and price. Complexity, duration and price are computed by methods of this class. Has a display function and an output operator. |
| `service` | The central class. It manages the lists of employees, appliances and requests, and implements the repair simulation. Requests move through the states registered, validated, assigned and active. |

## Project structure

```
.
├── main.cpp                # entry point and interactive menu
├── service.cpp / .h        # core logic and repair simulation
├── cerere_reparatie.*      # repair request (ticket)
├── echipa_service.*        # employee base class
├── tehnician.*             # technician
├── receptioner.*           # receptionist
├── supervizor.*            # supervisor
├── electrocasnic.*         # appliance base class
├── frigider.*              # refrigerator
├── televizor.*             # TV
├── masina_de_spalat.*      # washing machine
├── date.*                  # date
├── date_time.*             # date and time
├── io_fisier.h / io_fisiere.cpp   # reading data from files
└── tests/                  # input files used for testing
```

## Testing

The `tests/` folder contains the input files. For each of the three data groups there are three kinds of files: all data valid, all data invalid, and a mix of both.

| Data | Valid | Invalid | Mixed |
|------|-------|---------|-------|
| Employees | `angajati_valid.txt` | `angajati_invalid.txt` | `angajati_mix.txt` |
| Appliances | `electrocasnice_valid.txt` | `electrocasnice_invalid.txt` | `electrocasnice_mix.txt` |
| Repair requests | `cereri_valid.txt` | `cereri_invalid.txt` | `cereri_mix.txt` |

The invalid files cover cases such as a wrong CNP, an impossible date (e.g. day 32 or month 13), a name that is too short, an unknown employee or appliance type, negative or zero prices and capacities, and lines with missing fields. Invalid lines are rejected with an error instead of crashing the program.

### Input format

One record per line, fields separated by spaces.

- **Employees:** `ID TYPE LAST_NAME FIRST_NAME CNP DD MM YYYY CITY`, where `TYPE` is `R` (receptionist), `T` (technician) or `S` (supervisor).
  `6 T Popescu Ion 1900101123456 01 01 2022 Cluj`
- **Appliances:** `TYPE BRAND MODEL YEAR PRICE EXTRA`, where `TYPE` is `T` (TV), `F` (refrigerator) or `M` (washing machine), and `EXTRA` is the diagonal in cm, the freezer flag (`0` or `1`), or the capacity in kg, respectively.
  `T Samsung QLED_X1 2021 3000 125`
- **Repair requests:** `ID TYPE BRAND MODEL DD MM YYYY HH MM VALUE`, with the same `TYPE` letters as appliances.
  `1 T Samsung QLED_X1 10 01 2026 09 00 3`

By default the program loads one file from each group (see `main.cpp`). To try another case, change the file names it loads.
