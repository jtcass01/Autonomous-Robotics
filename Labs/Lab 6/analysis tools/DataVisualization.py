import numpy as np
import matplotlib.pyplot as plt
from sklearn.linear_model import LinearRegression

if __name__ == "__main__":
    distances = np.array(range(0,42,2)).reshape((-1, 1))
    analog_readings = np.array([52, 52, 52, 52, 52, 52, 52, 52, 52, 60, 68, 76, 76, 85, 85, 92, 100, 108, 115, 122, 130]).reshape((-1, 1))

    non_dead_distances = distances[9:, 0].reshape((-1, 1))
    non_dead_analog_readings = analog_readings[9:, 0].reshape((-1, 1))

    regressor = LinearRegression()
    regressor.fit(non_dead_distances, non_dead_analog_readings)

    plt.scatter(distances, analog_readings, c='blue', label="Sensor Response")
    x = np.linspace(0,40, 2)
    y = 3.04371*x + 4.81585
    plt.plot(x, y, c='black', label="Linear Fit")
    plt.xlabel('Centimeters')
    plt.ylabel('Analog Response')
    plt.legend()
    plt.show()

    print(non_dead_distances, non_dead_analog_readings)

    print(regressor.intercept_)
    print(regressor.coef_)
