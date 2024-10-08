# AirWatcher

**AirWatcher** is an application designed to monitor air quality. The system analyzes various environmental attributes like ozone (O3), nitrogen dioxide (NO2), sulfur dioxide (SO2), and particulate matter (PM10) across sensor networks.

## Features

- View air quality statistics across different regions.
- Analyze and rank sensors based on air quality measurements.
- Retrieve historical sensor data and perform statistical analysis.
- Extensive unit testing to ensure robustness.

## File Structure

- **src/**: Contains the source code, divided into:
  - `controllers/`: Main logic of the program, including the `Controller` class.
  - `models/`: Data models for entities like `Sensor`, `User`, and `Measurement`.
  - `views/`: Manages user interactions and console outputs.
  - `utils/`: Helper functions, including date-time conversions.
  
- **data/**: Stores the data files (CSV) used by the application, including sensor measurements, user data, and attributes.

- **tests/**: Contains unit tests for different components of the system.

## Setup and Usage

### Prerequisites

Make sure you have the following installed:
- C++ compiler (g++)
- Make

### Building the Project

To compile the project, run the following command from the root directory:

```bash
make
```

### Running the Program
Once built, run the application with:
```bash
./AirWatcher
```

### Running Unit Tests
The project comes with unit tests for critical components. To run the tests:
```bash
make test
./runTests
```

### Data
The application reads data from CSV files located in the data/ folder. Modify or replace these files to provide updated data sets for the system.

### License
This project is licensed under the MIT License. See the LICENSE file for details.
