import numpy as np
import matplotlib.pyplot as plt
from sklearn.linear_model import LinearRegression

if __name__ == "__main__":

    distances = np.array(range(13,0,-1)).reshape((-1, 1))
    analog_readings = np.array([97, 95, 88, 80, 75, 66, 57, 55, 55, 55, 55, 55, 55]).reshape((-1, 1))

    non_dead_distances = distances[:7, 0].reshape((-1, 1))
    non_dead_analog_readings = analog_readings[:7, 0].reshape((-1, 1))

    print(non_dead_distances, non_dead_analog_readings)

    regressor = LinearRegression()
    regressor.fit(non_dead_distances, non_dead_analog_readings)

    print(regressor.intercept_)
    print(regressor.coef_)

    plt.scatter(distances, analog_readings, c='blue', label="Sensor Response")
    x = np.linspace(0,13, 2)
    y = 6.82142857*x + 11.5
    plt.plot(x, y, c='black', label="Linear Fit")
    plt.xlabel('Inches')
    plt.ylabel('Analog Response')
    plt.legend()
    plt.show()

    print(non_dead_distances, non_dead_analog_readings)
