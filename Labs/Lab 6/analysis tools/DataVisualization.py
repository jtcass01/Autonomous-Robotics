import numpy as np
import matplotlib.pyplot as plt
from sklearn.linear_model import LinearRegression

if __name__ == "__main__":

    distances = np.array(range(0,32,2)).reshape((-1, 1))
    analog_readings = np.array([54, 54, 54, 54, 54, 54, 54, 54, 54, 64, 65, 68, 77, 88, 92, 100]).reshape((-1, 1))

    non_dead_analog_readings = analog_readings[9:, 0].reshape((-1, 1))
    non_dead_distances = distances[9:, 0].reshape((-1, 1))

    print(non_dead_distances, non_dead_analog_readings)

    regressor = LinearRegression()
    regressor.fit(non_dead_distances, non_dead_analog_readings)

    print("intercept:", regressor.intercept_)
    print("coefficient",  regressor.coef_)

    plt.scatter(distances, analog_readings, c='blue', label="Sensor Response")
    x = np.linspace(0,32, 2)
    y = 3.25*x + 1.14285714
    plt.plot(x, y, c='black', label="Linear Fit")
    plt.xlabel('Inches')
    plt.ylabel('Analog Response')
    plt.legend()
    plt.show()

    print(non_dead_distances, non_dead_analog_readings)
