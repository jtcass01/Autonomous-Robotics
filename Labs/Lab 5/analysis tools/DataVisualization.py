import numpy as np
import matplotlib.pyplot as plt

class DataVisualization():
    @staticmethod
    def plot_goal_and_actual(goal, actual_data, leftMotorPowers=None, rightMotorPowers=None):
        assert (leftMotorPowers is None and rightMotorPowers is None) or (leftMotorPowers is not None and rightMotorPowers is not None)

        time = np.zeros(actual_data.shape)

        if isinstance(goal, int):
            goal = np.ones(actual_data.shape) * goal

        for data_index in range(len(actual_data)):
            # time is represented in milliseconds
            time[data_index] = data_index * 100

        fig, axis = plt.subplots()
        axis.plot(time, goal, c='black', label="goal")
        axis.scatter(time, actual_data, s=10, marker='o', c='blue', label="actual_data")
        axis.set_ylim((goal[0] - 300, goal[0] + 300))
        axis.set_ylabel("Sensor Response")

        if leftMotorPowers is not None:
            axis2 = axis.twinx()
            axis2.scatter(time, leftMotorPowers, s=10, marker='s', c='green', label="Left Motor Power")
            axis2.scatter(time, rightMotorPowers, s=10, marker='s', c='yellow', label="Right Motor Power")
            axis2.set_ylim((-110, 110))
            axis2.set_ylabel("Motor Power")

        plt.xlabel("Time (ms)")
        plt.xlim(0, len(time)*100)
        plt.legend(loc=2, fontsize='small')
        plt.show()

    @staticmethod
    def menu():
        print("===== Data Visualization Menu =====")
        print("1 ) Plot goal versus actual")
        print("2 ) Plot goal versus actual with motor powers")
        print("0 ) quit")

        return input("Menu Response: ")

def convert_strlist_to_npint(strlist):
    list_representation = strlist.strip('][').split(", ")
    return np.array([int(data) for data in list_representation])

def input_goal_and_actual():
    goal = int(input("What was your goal value: "))
    # retrieve data
    actual_data = convert_strlist_to_npint(input("How did you actually perform: "))

    print(actual_data)

    return goal, actual_data


def input_motor_powers():
    leftMotorPowers = convert_strlist_to_npint(input("What were your left motor powers: "))
    rightMotorPowers = convert_strlist_to_npint(input("What were your right motor powers: "))

    return leftMotorPowers, rightMotorPowers


if __name__ == "__main__":
    response = ""

    while response != "quit" and response != "q" and response != "0":
        response = DataVisualization.menu()

        if response == "1":
            goal, actual_data = input_goal_and_actual()
            DataVisualization.plot_goal_and_actual(goal, actual_data)
        elif response == "2":
            goal, actual_data = input_goal_and_actual()
            leftMotorPowers, rightMotorPowers = input_motor_powers()
