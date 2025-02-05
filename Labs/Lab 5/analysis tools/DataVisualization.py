import numpy as np
import matplotlib.pyplot as plt

class DataVisualization():
    @staticmethod
    def plot_goal_and_actual(goal, actual_data, left_motor_powers=None, right_motor_powers=None):
        assert (left_motor_powers is None and right_motor_powers is None) or (left_motor_powers is not None and right_motor_powers is not None)

        time = np.zeros(actual_data.shape)

        if isinstance(goal, int):
            goal = np.ones(actual_data.shape) * goal

        for data_index in range(len(actual_data)):
            # time is represented in milliseconds
            time[data_index] = data_index * 100

        fig, axis = plt.subplots()
        axis.plot(time, goal, c='black', label="goal")
        axis.scatter(time, actual_data, s=10, marker='o', c='blue', label="actual_data")
        axis.scatter(time, actual_data + -goal, s=10, marker='o', c='red', label='error')
        axis.legend()
        axis.set_ylim((-2000, 4096))
        axis.set_ylabel("Sensor Response")

        if left_motor_powers is not None:
            axis2 = axis.twinx()
            axis2.scatter(time, left_motor_powers, s=10, marker='s', c='green', label="Left Motor Power")
            axis2.scatter(time, right_motor_powers, s=10, marker='s', c='yellow', label="Right Motor Power")
            axis2.legend()
            axis2.set_ylim((-105, 105))
            axis2.set_ylabel("Motor Power")

        plt.xlabel("Time (ms)")
        plt.xlim(0, len(time)*100)
        plt.show()

    @staticmethod
    def menu():
        print("===== Data Visualization Menu =====")
        print("1 ) Plot goal versus actual")
        print("2 ) Plot goal versus actual with motor powers")
        print("3 ) Data to csv")
        print("4 ) Plot and Data to CSV")
        print("0 ) quit")

        return input("Menu Response: ")

    @staticmethod
    def data_to_csv(file_name, actual_data, goal, left_motor_powers, right_motor_powers):
        with open(file_name, "w+") as csv_file:
            csv_file.write("{},{},{},{}\n".format("actual_data", "error", "left_motor_powers", "right_motor_powers"))

            for data_index in range(len(actual_data)):
                if int(actual_data[data_index]) == 0:
                    break
                csv_file.write("{},{},{},{}\n".format(actual_data[data_index], goal-actual_data[data_index], left_motor_powers[data_index], right_motor_powers[data_index]))

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
    left_motor_powers = convert_strlist_to_npint(input("What were your left motor powers: "))
    right_motor_powers = convert_strlist_to_npint(input("What were your right motor powers: "))

    return left_motor_powers, right_motor_powers


if __name__ == "__main__":
    response = ""

    while response != "quit" and response != "q" and response != "0":
        response = DataVisualization.menu()

        if response == "1":
            goal, actual_data = input_goal_and_actual()
            DataVisualization.plot_goal_and_actual(goal, actual_data)
        elif response == "2":
            goal, actual_data = input_goal_and_actual()
            left_motor_powers, right_motor_powers = input_motor_powers()
            DataVisualization.plot_goal_and_actual(goal, actual_data, left_motor_powers=left_motor_powers, right_motor_powers=right_motor_powers)
        elif response == "3":
            file_name = input("file_name: ")
            goal, actual_data = input_goal_and_actual()
            left_motor_powers, right_motor_powers = input_motor_powers()
            DataVisualization.data_to_csv(file_name, actual_data, goal, left_motor_powers, right_motor_powers)
        elif response == "4":
            file_name = input("file_name: ")
            goal, actual_data = input_goal_and_actual()
            left_motor_powers, right_motor_powers = input_motor_powers()
            DataVisualization.data_to_csv(file_name, actual_data, goal, left_motor_powers, right_motor_powers)
            DataVisualization.plot_goal_and_actual(goal, actual_data, left_motor_powers=left_motor_powers, right_motor_powers=right_motor_powers)
