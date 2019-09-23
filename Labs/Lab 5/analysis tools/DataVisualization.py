import numpy as np
import matplotlib.pyplot as plt

class DataVisualization():
    @staticmethod
    def plot_goal_and_actual(goal, actual_data):
        time = np.zeros(actual_data.shape)

        if isinstance(goal, int):
            goal = np.ones(actual_data.shape) * goal

        for data_index in range(len(actual_data)):
            # time is represented in milliseconds
            time[data_index] = data_index * 100

        fig, axis = plt.subplots()
        axis.plot(time, goal, c='r', label="goal")
        axis.scatter(time, actual_data, s=10, marker='o', c='b', label="actual_data")

        plt.xlabel("Time (ms)")
        plt.xlim((0, len(time)*100))
        plt.ylabel("Sensor Response")
        plt.ylim((goal[0] - 250, goal[0] + 250))
        plt.legend(loc=2, fontsize='small')
        plt.show()

    @staticmethod
    def menu():
        print("===== Data Visualization Menu =====")
        print("1 ) Plot goal versus actual")
        print("0 ) quit")

        return input("Menu Response: ")

def input_goal_and_actual():
    goal = int(input("What was your goal value: "))
    # retrieve data
    actual_data = input("How did you actually perform: ").strip('][').split(", ")
    # convert to int
    actual_data = np.array([int(data) for data in actual_data])

    return goal, actual_data

if __name__ == "__main__":
    response = ""

    while response != "quit" and response != "q" and response != "0":
        response = DataVisualization.menu()

        if response == "1":
            goal, actual_data = input_goal_and_actual()
            DataVisualization.plot_goal_and_actual(goal, actual_data)
