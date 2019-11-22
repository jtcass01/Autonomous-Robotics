import numpy as np

"""
top_left run ouput

xReadings : [62, 62, 62, 60, 62, 61, 61, 62, 62, 60, 60, 62, 62, 60, 61, 62, 60, 60, 61, 62, 60, 60, 60, 61, 62, 61, 60, 61, 61, 62, 60, 61, 62, 61, 60, 61, 60, 61, 60, 64, 61, 62, 62, 61, 62, 60, 62, 61, 61, 61, 60, 60, 42, 60, 62, 62, 61, 60, 61, 61, 61, 61, 60, 60, 62, 60, 61, 61, 61, 60, 62, 61, 60, 62, 61, 62, 60, 60, 62, 60, 46, 47, 84, 57, 61, 60, 61, 60, 60, 60, 60, 62, 62, 60, 60, 60, 61, 61, 61, 61, 60, 62, 61, 62, 60, 61, 60, 61, 62, 62, 62, 62, 61, 62, 62, 60, 62, 120, 61, 62, 61, 60, 61, 62, 60, 60, 60, 62, 60, 60, 61, 61, 60, 60, 60, 62, 60, 60, 60, 62, 61, 60, 62, 60, 60, 60, 61, 60, 60, 61, 2]
xRAReadings : [62, 62, 62, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 61, 61, 60, 61, 61, 61, 61, 60, 60, 60, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 60, 58, 57, 58, 58, 58, 58, 58, 61, 61, 61, 60, 60, 60, 60, 60, 60, 60, 60, 61, 60, 60, 61, 61, 61, 61, 60, 61, 61, 58, 56, 59, 59, 59, 59, 59, 61, 63, 59, 60, 62, 62, 61, 61, 60, 60, 60, 60, 60, 60, 60, 61, 61, 61, 61, 60, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 69, 69, 69, 69, 69, 69, 69, 61, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 81]
yReadings : [81, 80, 81, 81, 81, 81, 81, 81, 81, 81, 81, 80, 81, 80, 81, 81, 80, 81, 81, 81, 81, 80, 80, 81, 81, 81, 81, 81, 81, 80, 81, 80, 81, 81, 79, 81, 81, 81, 81, 87, 81, 81, 81, 81, 80, 80, 80, 81, 80, 81, 80, 80, 79, 81, 81, 80, 81, 81, 80, 81, 81, 79, 81, 81, 81, 81, 81, 81, 81, 81, 80, 80, 81, 81, 81, 80, 81, 80, 81, 81, 87, 77, 1, 81, 81, 81, 81, 81, 81, 80, 80, 81, 81, 81, 81, 81, 80, 81, 80, 80, 80, 81, 80, 81, 81, 81, 81, 81, 81, 81, 80, 81, 80, 81, 81, 80, 81, 115, 81, 81, 81, 81, 81, 80, 81, 81, 81, 81, 81, 80, 81, 81, 80, 81, 81, 80, 80, 81, 81, 80, 77, 81, 81, 81, 81, 81, 80, 81, 81, 81, 62]
yRAReadings : [81, 80, 80, 80, 80, 80, 80, 80, 81, 81, 81, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 81, 81, 81, 81, 81, 81, 81, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 81, 81, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 81, 81, 69, 69, 69, 69, 69, 69, 69, 80, 80, 81, 81, 81, 81, 81, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 81, 80, 80, 80, 80, 80, 80, 80, 85, 85, 85, 85, 85, 85, 85, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 62]

"""
def top_left():
    print("Top Left")
    x = np.array([62, 62, 62, 60, 62, 61, 61, 62, 62, 60, 60, 62, 62, 60, 61, 62, 60, 60, 61, 62, 60, 60, 60, 61, 62, 61, 60, 61, 61, 62, 60, 61, 62, 61, 60, 61, 60, 61, 60, 64, 61, 62, 62, 61, 62, 60, 62, 61, 61, 61, 60, 60, 42, 60, 62, 62, 61, 60, 61, 61, 61, 61, 60, 60, 62, 60, 61, 61, 61, 60, 62, 61, 60, 62, 61, 62, 60, 60, 62, 60, 46, 47, 84, 57, 61, 60, 61, 60, 60, 60, 60, 62, 62, 60, 60, 60, 61, 61, 61, 61, 60, 62, 61, 62, 60, 61, 60, 61, 62, 62, 62, 62, 61, 62, 62, 60, 62, 120, 61, 62, 61, 60, 61, 62, 60, 60, 60, 62, 60, 60, 61, 61, 60, 60, 60, 62, 60, 60, 60, 62, 61, 60, 62, 60, 60, 60, 61, 60, 60, 61])
    xRA = np.array([62, 62, 62, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 61, 61, 60, 61, 61, 61, 61, 60, 60, 60, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 60, 58, 57, 58, 58, 58, 58, 58, 61, 61, 61, 60, 60, 60, 60, 60, 60, 60, 60, 61, 60, 60, 61, 61, 61, 61, 60, 61, 61, 58, 56, 59, 59, 59, 59, 59, 61, 63, 59, 60, 62, 62, 61, 61, 60, 60, 60, 60, 60, 60, 60, 61, 61, 61, 61, 60, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 69, 69, 69, 69, 69, 69, 69, 61, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60])
    y = np.array([81, 80, 81, 81, 81, 81, 81, 81, 81, 81, 81, 80, 81, 80, 81, 81, 80, 81, 81, 81, 81, 80, 80, 81, 81, 81, 81, 81, 81, 80, 81, 80, 81, 81, 79, 81, 81, 81, 81, 87, 81, 81, 81, 81, 80, 80, 80, 81, 80, 81, 80, 80, 79, 81, 81, 80, 81, 81, 80, 81, 81, 79, 81, 81, 81, 81, 81, 81, 81, 81, 80, 80, 81, 81, 81, 80, 81, 80, 81, 81, 87, 77, 1, 81, 81, 81, 81, 81, 81, 80, 80, 81, 81, 81, 81, 81, 80, 81, 80, 80, 80, 81, 80, 81, 81, 81, 81, 81, 81, 81, 80, 81, 80, 81, 81, 80, 81, 115, 81, 81, 81, 81, 81, 80, 81, 81, 81, 81, 81, 80, 81, 81, 80, 81, 81, 80, 80, 81, 81, 80, 77, 81, 81, 81, 81, 81, 80, 81, 81, 81])
    yRA = np.array([81, 80, 80, 80, 80, 80, 80, 80, 81, 81, 81, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 81, 81, 81, 81, 81, 81, 81, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 81, 81, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 81, 81, 69, 69, 69, 69, 69, 69, 69, 80, 80, 81, 81, 81, 81, 81, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 81, 80, 80, 80, 80, 80, 80, 80, 85, 85, 85, 85, 85, 85, 85, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80])
    print("x, average = {}, standard deviation = {}, min = {}, max = {}".format(x.mean(), x.std(), min(x), max(x)))
    print("xRa, average = {}, standard deviation = {}, min = {}, max = {}".format(xRA.mean(), xRA.std(), min(xRA), max(xRA)))
    print("y, average = {}, standard deviation = {}, min = {}, max = {}".format(y.mean(), y.std(), min(y), max(y)))
    print("yRa, average = {}, standard deviation = {}, min = {}, max = {}".format(yRA.mean(), yRA.std(), min(yRA), max(yRA)))

"""
top_right run ouput

xReadings : [85, 104, 104, 100, 100, 105, 104, 104, 105, 100, 100, 105, 104, 104, 105, 101, 113, 134, 110, 105, 101, 101, 134, 104, 101, 100, 104, 104, 104, 100, 104, 105, 100, 107, 104, 104, 104, 104, 101, 100, 101, 104, 101, 107, 104, 104, 113, 110, 104, 101, 104, 104, 100, 101, 101, 100, 104, 100, 104, 101, 104, 107, 101, 104, 105, 101, 113, 104, 104, 104, 101, 107, 100, 104, 104, 100, 104, 113, 104, 101, 104, 101, 101, 104, 100, 100, 104, 104, 101, 100, 100, 100, 101, 104, 104, 104, 104, 110, 109, 107, 101, 113, 101, 113, 150, 52, 143, 104, 104, 104, 104, 104, 110, 104, 104, 107, 100, 104, 104, 113, 101, 105, 101, 104, 104, 101, 112, 104, 112, 104, 104, 104, 104, 112, 105, 101, 101, 104, 100, 104, 104, 107, 104, 104, 104, 113, 100, 101, 110, 113, 4]
xRAReadings : [99, 100, 101, 101, 101, 101, 100, 103, 103, 102, 102, 103, 103, 103, 103, 102, 104, 109, 110, 107, 105, 104, 110, 109, 108, 106, 106, 106, 107, 102, 102, 103, 103, 103, 103, 103, 104, 104, 103, 103, 102, 102, 102, 102, 102, 103, 104, 106, 106, 106, 105, 105, 105, 103, 102, 101, 102, 101, 101, 101, 102, 102, 103, 103, 103, 103, 105, 105, 104, 105, 104, 104, 104, 103, 103, 102, 102, 104, 104, 104, 104, 103, 104, 104, 102, 101, 102, 102, 102, 101, 101, 101, 101, 101, 101, 101, 102, 103, 105, 106, 105, 106, 106, 107, 113, 105, 110, 110, 109, 110, 108, 102, 110, 104, 104, 105, 104, 104, 104, 105, 104, 104, 104, 104, 104, 104, 104, 104, 105, 105, 105, 105, 106, 106, 106, 104, 104, 104, 103, 104, 104, 105, 104, 104, 104, 105, 105, 104, 105, 106, 91]
yReadings : [78, 77, 77, 80, 80, 77, 77, 77, 77, 80, 80, 77, 77, 77, 77, 80, 91, 22, 91, 77, 80, 80, 107, 77, 80, 80, 77, 79, 79, 82, 77, 77, 80, 77, 77, 77, 77, 77, 80, 80, 80, 77, 80, 77, 77, 77, 91, 91, 77, 80, 77, 77, 80, 80, 80, 80, 77, 80, 77, 80, 76, 77, 80, 77, 77, 80, 91, 77, 79, 77, 80, 77, 80, 77, 77, 80, 77, 91, 77, 80, 77, 80, 80, 77, 79, 80, 77, 77, 80, 80, 80, 82, 80, 77, 77, 77, 77, 91, 91, 77, 80, 91, 80, 91, 115, 78, 16, 77, 77, 77, 77, 77, 91, 77, 77, 77, 80, 76, 77, 91, 80, 77, 79, 77, 77, 80, 91, 77, 92, 77, 77, 76, 78, 91, 77, 80, 80, 77, 80, 77, 77, 77, 77, 77, 77, 91, 80, 80, 91, 91, 113]
yRAReadings : [84, 82, 80, 80, 80, 80, 78, 77, 77, 78, 78, 77, 77, 77, 77, 78, 79, 71, 91, 84, 82, 82, 87, 85, 84, 83, 83, 82, 82, 79, 79, 78, 78, 78, 78, 78, 77, 77, 77, 77, 78, 78, 78, 78, 78, 78, 79, 81, 81, 81, 81, 81, 81, 80, 78, 79, 78, 79, 79, 79, 78, 78, 78, 78, 77, 78, 79, 79, 80, 79, 80, 80, 80, 78, 78, 78, 78, 79, 79, 79, 79, 80, 80, 80, 78, 79, 78, 78, 78, 78, 79, 79, 79, 79, 79, 79, 78, 80, 81, 81, 81, 83, 83, 85, 89, 87, 78, 78, 76, 75, 73, 68, 70, 79, 79, 79, 79, 79, 79, 79, 79, 79, 80, 79, 79, 80, 80, 79, 81, 81, 81, 81, 81, 81, 81, 79, 79, 79, 80, 77, 77, 77, 77, 77, 77, 79, 79, 79, 81, 83, 113]

"""
def top_right():
    print("\nTop Right")
    x = np.array([85, 104, 104, 100, 100, 105, 104, 104, 105, 100, 100, 105, 104, 104, 105, 101, 113, 134, 110, 105, 101, 101, 134, 104, 101, 100, 104, 104, 104, 100, 104, 105, 100, 107, 104, 104, 104, 104, 101, 100, 101, 104, 101, 107, 104, 104, 113, 110, 104, 101, 104, 104, 100, 101, 101, 100, 104, 100, 104, 101, 104, 107, 101, 104, 105, 101, 113, 104, 104, 104, 101, 107, 100, 104, 104, 100, 104, 113, 104, 101, 104, 101, 101, 104, 100, 100, 104, 104, 101, 100, 100, 100, 101, 104, 104, 104, 104, 110, 109, 107, 101, 113, 101, 113, 150, 52, 143, 104, 104, 104, 104, 104, 110, 104, 104, 107, 100, 104, 104, 113, 101, 105, 101, 104, 104, 101, 112, 104, 112, 104, 104, 104, 104, 112, 105, 101, 101, 104, 100, 104, 104, 107, 104, 104, 104, 113, 100, 101, 110, 113])
    xRA = np.array([99, 100, 101, 101, 101, 101, 100, 103, 103, 102, 102, 103, 103, 103, 103, 102, 104, 109, 110, 107, 105, 104, 110, 109, 108, 106, 106, 106, 107, 102, 102, 103, 103, 103, 103, 103, 104, 104, 103, 103, 102, 102, 102, 102, 102, 103, 104, 106, 106, 106, 105, 105, 105, 103, 102, 101, 102, 101, 101, 101, 102, 102, 103, 103, 103, 103, 105, 105, 104, 105, 104, 104, 104, 103, 103, 102, 102, 104, 104, 104, 104, 103, 104, 104, 102, 101, 102, 102, 102, 101, 101, 101, 101, 101, 101, 101, 102, 103, 105, 106, 105, 106, 106, 107, 113, 105, 110, 110, 109, 110, 108, 102, 110, 104, 104, 105, 104, 104, 104, 105, 104, 104, 104, 104, 104, 104, 104, 104, 105, 105, 105, 105, 106, 106, 106, 104, 104, 104, 103, 104, 104, 105, 104, 104, 104, 105, 105, 104, 105, 106])
    y = np.array([78, 77, 77, 80, 80, 77, 77, 77, 77, 80, 80, 77, 77, 77, 77, 80, 91, 22, 91, 77, 80, 80, 107, 77, 80, 80, 77, 79, 79, 82, 77, 77, 80, 77, 77, 77, 77, 77, 80, 80, 80, 77, 80, 77, 77, 77, 91, 91, 77, 80, 77, 77, 80, 80, 80, 80, 77, 80, 77, 80, 76, 77, 80, 77, 77, 80, 91, 77, 79, 77, 80, 77, 80, 77, 77, 80, 77, 91, 77, 80, 77, 80, 80, 77, 79, 80, 77, 77, 80, 80, 80, 82, 80, 77, 77, 77, 77, 91, 91, 77, 80, 91, 80, 91, 115, 78, 16, 77, 77, 77, 77, 77, 91, 77, 77, 77, 80, 76, 77, 91, 80, 77, 79, 77, 77, 80, 91, 77, 92, 77, 77, 76, 78, 91, 77, 80, 80, 77, 80, 77, 77, 77, 77, 77, 77, 91, 80, 80, 91, 91])
    yRA = np.array([84, 82, 80, 80, 80, 80, 78, 77, 77, 78, 78, 77, 77, 77, 77, 78, 79, 71, 91, 84, 82, 82, 87, 85, 84, 83, 83, 82, 82, 79, 79, 78, 78, 78, 78, 78, 77, 77, 77, 77, 78, 78, 78, 78, 78, 78, 79, 81, 81, 81, 81, 81, 81, 80, 78, 79, 78, 79, 79, 79, 78, 78, 78, 78, 77, 78, 79, 79, 80, 79, 80, 80, 80, 78, 78, 78, 78, 79, 79, 79, 79, 80, 80, 80, 78, 79, 78, 78, 78, 78, 79, 79, 79, 79, 79, 79, 78, 80, 81, 81, 81, 83, 83, 85, 89, 87, 78, 78, 76, 75, 73, 68, 70, 79, 79, 79, 79, 79, 79, 79, 79, 79, 80, 79, 79, 80, 80, 79, 81, 81, 81, 81, 81, 81, 81, 79, 79, 79, 80, 77, 77, 77, 77, 77, 77, 79, 79, 79, 81, 83])
    print("x, average = {}, standard deviation = {}, min = {}, max = {}".format(x.mean(), x.std(), min(x), max(x)))
    print("xRa, average = {}, standard deviation = {}, min = {}, max = {}".format(xRA.mean(), xRA.std(), min(xRA), max(xRA)))
    print("y, average = {}, standard deviation = {}, min = {}, max = {}".format(y.mean(), y.std(), min(y), max(y)))
    print("yRa, average = {}, standard deviation = {}, min = {}, max = {}".format(yRA.mean(), yRA.std(), min(yRA), max(yRA)))

"""
mid run ouput
xReadings : [80, 79, 79, 80, 79, 79, 79, 79, 79, 79, 79, 79, 79, 80, 79, 80, 79, 80, 80, 79, 79, 80, 134, 79, 79, 79, 80, 79, 80, 79, 79, 79, 79, 80, 80, 79, 80, 79, 80, 79, 79, 79, 80, 79, 80, 79, 79, 80, 80, 79, 79, 79, 80, 79, 80, 79, 79, 79, 80, 79, 79, 79, 80, 79, 79, 79, 79, 79, 80, 79, 79, 79, 80, 66, 79, 79, 79, 80, 80, 79, 79, 79, 79, 151, 111, 79, 80, 79, 79, 79, 80, 79, 79, 80, 79, 79, 79, 80, 80, 79, 79, 80, 79, 80, 79, 80, 80, 79, 79, 79, 79, 79, 79, 80, 80, 78, 79, 78, 79, 79, 79, 79, 80, 80, 79, 79, 80, 79, 80, 79, 80, 63, 79, 80, 79, 79, 79, 79, 79, 78, 79, 79, 79, 79, 79, 79, 79, 80, 79, 79, 3]
xRAReadings : [79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 87, 87, 87, 87, 87, 87, 87, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 77, 77, 77, 77, 77, 77, 77, 79, 79, 79, 89, 94, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 78, 78, 79, 79, 79, 79, 79, 79, 79, 79, 79, 77, 77, 77, 77, 77, 77, 76, 79, 79, 78, 78, 78, 78, 78, 78, 79, 79, 79, 79, 91]
yReadings : [91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 107, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 95, 91, 91, 91, 91, 91, 91, 91, 91, 91, 115, 110, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 79]
yRAReadings : [91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 93, 93, 93, 93, 93, 93, 93, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 94, 97, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 79]
"""
def mid():
    print("\nMid")
    x = np.array([80, 79, 79, 80, 79, 79, 79, 79, 79, 79, 79, 79, 79, 80, 79, 80, 79, 80, 80, 79, 79, 80, 134, 79, 79, 79, 80, 79, 80, 79, 79, 79, 79, 80, 80, 79, 80, 79, 80, 79, 79, 79, 80, 79, 80, 79, 79, 80, 80, 79, 79, 79, 80, 79, 80, 79, 79, 79, 80, 79, 79, 79, 80, 79, 79, 79, 79, 79, 80, 79, 79, 79, 80, 66, 79, 79, 79, 80, 80, 79, 79, 79, 79, 151, 111, 79, 80, 79, 79, 79, 80, 79, 79, 80, 79, 79, 79, 80, 80, 79, 79, 80, 79, 80, 79, 80, 80, 79, 79, 79, 79, 79, 79, 80, 80, 78, 79, 78, 79, 79, 79, 79, 80, 80, 79, 79, 80, 79, 80, 79, 80, 63, 79, 80, 79, 79, 79, 79, 79, 78, 79, 79, 79, 79, 79, 79, 79, 80, 79, 79])
    xRA = np.array([79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 87, 87, 87, 87, 87, 87, 87, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 77, 77, 77, 77, 77, 77, 77, 79, 79, 79, 89, 94, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 78, 78, 79, 79, 79, 79, 79, 79, 79, 79, 79, 77, 77, 77, 77, 77, 77, 76, 79, 79, 78, 78, 78, 78, 78, 78, 79, 79, 79, 79])
    y = np.array([91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 107, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 95, 91, 91, 91, 91, 91, 91, 91, 91, 91, 115, 110, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91])
    yRA = np.array([91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 93, 93, 93, 93, 93, 93, 93, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 94, 97, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91])
    print("x, average = {}, standard deviation = {}, min = {}, max = {}".format(x.mean(), x.std(), min(x), max(x)))
    print("xRa, average = {}, standard deviation = {}, min = {}, max = {}".format(xRA.mean(), xRA.std(), min(xRA), max(xRA)))
    print("y, average = {}, standard deviation = {}, min = {}, max = {}".format(y.mean(), y.std(), min(y), max(y)))
    print("yRa, average = {}, standard deviation = {}, min = {}, max = {}".format(yRA.mean(), yRA.std(), min(yRA), max(yRA)))

"""
bottom_left run ouput

xReadings : [61, 47, 61, 61, 61, 61, 61, 61, 61, 61, 61, 39, 49, 151, 60, 61, 60, 61, 61, 61, 60, 61, 61, 61, 60, 60, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 60, 61, 60, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 52, 61, 61, 60, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 60, 61, 61, 60, 61, 61, 60, 80, 32, 25, 60, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 60, 60, 60, 61, 61, 61, 60, 60, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 60, 48, 61, 60, 3]
xRAReadings : [60, 56, 57, 58, 58, 58, 59, 59, 61, 61, 61, 57, 56, 69, 68, 68, 68, 68, 71, 73, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 60, 60, 60, 60, 60, 60, 60, 60, 60, 61, 61, 61, 61, 61, 61, 61, 61, 61, 59, 59, 61, 60, 60, 60, 60, 60, 60, 60, 61, 61, 61, 61, 61, 61, 60, 60, 60, 60, 60, 60, 60, 80, 56, 45, 49, 51, 53, 54, 51, 55, 60, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 61, 61, 61, 61, 61, 61, 61, 61, 60, 59, 59, 58, 102]
yReadings : [102, 103, 102, 102, 101, 102, 102, 102, 102, 102, 102, 106, 104, 115, 102, 101, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 101, 102, 102, 101, 102, 101, 102, 103, 102, 102, 102, 101, 102, 102, 102, 102, 102, 102, 103, 102, 102, 101, 102, 102, 102, 103, 102, 102, 102, 102, 102, 102, 102, 103, 102, 102, 102, 101, 102, 102, 102, 102, 102, 102, 107, 102, 102, 102, 102, 101, 103, 101, 103, 102, 102, 102, 102, 102, 102, 102, 101, 102, 102, 102, 102, 102, 102, 64, 103, 105, 102, 103, 102, 102, 102, 102, 102, 101, 102, 102, 102, 102, 103, 102, 101, 102, 102, 102, 102, 102, 102, 103, 102, 101, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 60]
yRAReadings : [102, 102, 102, 102, 102, 102, 102, 102, 101, 101, 101, 102, 102, 104, 104, 104, 104, 104, 104, 103, 101, 101, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 102, 101, 102, 102, 101, 101, 101, 101, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 101, 101, 101, 101, 102, 102, 102, 102, 102, 101, 102, 101, 102, 102, 102, 102, 102, 102, 102, 102, 101, 101, 101, 101, 101, 101, 101, 64, 83, 90, 93, 95, 96, 97, 102, 102, 102, 102, 101, 101, 101, 101, 102, 102, 102, 102, 102, 102, 102, 101, 101, 102, 102, 102, 102, 102, 102, 102, 101, 101, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 60]

"""
def bottom_left():
    print("\nBottom Left")
    x = np.array([61, 47, 61, 61, 61, 61, 61, 61, 61, 61, 61, 39, 49, 151, 60, 61, 60, 61, 61, 61, 60, 61, 61, 61, 60, 60, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 60, 61, 60, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 52, 61, 61, 60, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 60, 61, 61, 60, 61, 61, 60, 80, 32, 25, 60, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 60, 60, 60, 61, 61, 61, 60, 60, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 60, 48, 61, 60])
    xRA = np.array([60, 56, 57, 58, 58, 58, 59, 59, 61, 61, 61, 57, 56, 69, 68, 68, 68, 68, 71, 73, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 60, 60, 60, 60, 60, 60, 60, 60, 60, 61, 61, 61, 61, 61, 61, 61, 61, 61, 59, 59, 61, 60, 60, 60, 60, 60, 60, 60, 61, 61, 61, 61, 61, 61, 60, 60, 60, 60, 60, 60, 60, 80, 56, 45, 49, 51, 53, 54, 51, 55, 60, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 61, 61, 61, 61, 61, 61, 61, 61, 60, 59, 59, 58])
    y = np.array([102, 103, 102, 102, 101, 102, 102, 102, 102, 102, 102, 106, 104, 115, 102, 101, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 101, 102, 102, 101, 102, 101, 102, 103, 102, 102, 102, 101, 102, 102, 102, 102, 102, 102, 103, 102, 102, 101, 102, 102, 102, 103, 102, 102, 102, 102, 102, 102, 102, 103, 102, 102, 102, 101, 102, 102, 102, 102, 102, 102, 107, 102, 102, 102, 102, 101, 103, 101, 103, 102, 102, 102, 102, 102, 102, 102, 101, 102, 102, 102, 102, 102, 102, 64, 103, 105, 102, 103, 102, 102, 102, 102, 102, 101, 102, 102, 102, 102, 103, 102, 101, 102, 102, 102, 102, 102, 102, 103, 102, 101, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102])
    yRA = np.array([102, 102, 102, 102, 102, 102, 102, 102, 101, 101, 101, 102, 102, 104, 104, 104, 104, 104, 104, 103, 101, 101, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 102, 101, 102, 102, 101, 101, 101, 101, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 101, 101, 101, 101, 102, 102, 102, 102, 102, 101, 102, 101, 102, 102, 102, 102, 102, 102, 102, 102, 101, 101, 101, 101, 101, 101, 101, 64, 83, 90, 93, 95, 96, 97, 102, 102, 102, 102, 101, 101, 101, 101, 102, 102, 102, 102, 102, 102, 102, 101, 101, 102, 102, 102, 102, 102, 102, 102, 101, 101, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102])
    print("x, average = {}, standard deviation = {}, min = {}, max = {}".format(x.mean(), x.std(), min(x), max(x)))
    print("xRa, average = {}, standard deviation = {}, min = {}, max = {}".format(xRA.mean(), xRA.std(), min(xRA), max(xRA)))
    print("y, average = {}, standard deviation = {}, min = {}, max = {}".format(y.mean(), y.std(), min(y), max(y)))
    print("yRa, average = {}, standard deviation = {}, min = {}, max = {}".format(yRA.mean(), yRA.std(), min(yRA), max(yRA)))

"""
bottom_right run ouput

xReadings : [97, 97, 97, 97, 73, 80, 97, 97, 97, 97, 97, 97, 111, 97, 97, 97, 97, 97, 97, 97, 97, 97, 82, 66, 97, 84, 97, 97, 97, 97, 87, 81, 88, 97, 97, 97, 97, 97, 97, 97, 97, 86, 80, 84, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 34, 81, 70, 97, 97, 97, 97, 97, 97, 97, 83, 97, 97, 97, 62, 97, 25, 97, 151, 98, 24, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 34, 97, 97, 97, 97, 39, 135, 47, 86, 67, 97, 70, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 80, 87, 151, 97, 97, 97, 115, 97, 97, 97, 97, 97, 97, 97, 70, 65, 97, 97, 97, 97, 97, 97, 97, 67, 97, 97, 97, 97, 97, 97, 97, 97, 65, 86, 101, 18]
xRAReadings : [97, 97, 97, 97, 85, 80, 88, 97, 97, 97, 97, 97, 111, 97, 97, 97, 97, 97, 97, 97, 97, 97, 82, 66, 81, 84, 97, 97, 97, 97, 87, 84, 88, 97, 97, 97, 97, 97, 97, 97, 97, 86, 83, 84, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 34, 57, 70, 97, 97, 97, 97, 97, 97, 97, 83, 90, 97, 97, 79, 97, 25, 61, 91, 98, 61, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 34, 97, 97, 97, 97, 39, 87, 73, 76, 74, 97, 70, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 80, 83, 106, 103, 97, 97, 115, 97, 97, 97, 97, 97, 97, 97, 70, 65, 97, 97, 97, 97, 97, 97, 97, 67, 97, 97, 97, 97, 97, 97, 97, 97, 65, 86, 93, 100]
yReadings : [100, 100, 100, 99, 55, 67, 98, 99, 99, 97, 99, 101, 109, 99, 100, 99, 97, 102, 96, 99, 99, 98, 99, 99, 98, 99, 97, 97, 100, 99, 105, 100, 4, 99, 99, 97, 96, 97, 98, 99, 97, 94, 103, 99, 98, 97, 99, 98, 96, 98, 99, 96, 96, 99, 96, 99, 96, 100, 96, 13, 99, 110, 99, 97, 99, 99, 96, 98, 99, 97, 99, 97, 97, 96, 100, 9, 97, 115, 99, 115, 102, 98, 100, 99, 96, 99, 98, 99, 97, 99, 12, 97, 98, 99, 98, 98, 107, 109, 105, 114, 98, 99, 98, 99, 98, 100, 99, 99, 99, 99, 99, 98, 98, 99, 97, 99, 22, 115, 100, 100, 98, 99, 97, 99, 99, 99, 99, 100, 100, 105, 99, 99, 98, 97, 99, 102, 99, 100, 100, 98, 98, 97, 99, 99, 97, 99, 99, 97, 98, 107, 97]
yRAReadings : [100, 100, 100, 99, 77, 67, 82, 99, 99, 97, 98, 101, 109, 99, 99, 99, 97, 102, 96, 99, 99, 98, 99, 99, 98, 99, 97, 97, 100, 99, 105, 102, 4, 99, 99, 97, 96, 97, 97, 99, 98, 94, 98, 99, 98, 97, 99, 98, 96, 97, 99, 97, 97, 97, 96, 99, 96, 100, 96, 13, 56, 110, 99, 97, 99, 99, 97, 98, 99, 97, 98, 97, 97, 96, 100, 9, 53, 73, 99, 107, 102, 98, 100, 99, 96, 97, 98, 99, 97, 99, 12, 97, 98, 99, 98, 98, 102, 104, 104, 106, 98, 99, 98, 99, 98, 100, 99, 99, 99, 99, 99, 98, 98, 99, 98, 99, 60, 78, 84, 100, 99, 99, 97, 99, 99, 99, 99, 100, 100, 105, 99, 99, 98, 97, 99, 100, 99, 99, 100, 98, 98, 97, 98, 99, 98, 98, 99, 97, 98, 102, 97]

"""
def bottom_right():
    print("\nBottom Right")
    x = np.array([97, 97, 97, 97, 73, 80, 97, 97, 97, 97, 97, 97, 111, 97, 97, 97, 97, 97, 97, 97, 97, 97, 82, 66, 97, 84, 97, 97, 97, 97, 87, 81, 88, 97, 97, 97, 97, 97, 97, 97, 97, 86, 80, 84, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 34, 81, 70, 97, 97, 97, 97, 97, 97, 97, 83, 97, 97, 97, 62, 97, 25, 97, 151, 98, 24, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 34, 97, 97, 97, 97, 39, 135, 47, 86, 67, 97, 70, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 80, 87, 151, 97, 97, 97, 115, 97, 97, 97, 97, 97, 97, 97, 70, 65, 97, 97, 97, 97, 97, 97, 97, 67, 97, 97, 97, 97, 97, 97, 97, 97, 65, 86, 101])
    xRA = np.array([97, 97, 97, 97, 85, 80, 88, 97, 97, 97, 97, 97, 111, 97, 97, 97, 97, 97, 97, 97, 97, 97, 82, 66, 81, 84, 97, 97, 97, 97, 87, 84, 88, 97, 97, 97, 97, 97, 97, 97, 97, 86, 83, 84, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 34, 57, 70, 97, 97, 97, 97, 97, 97, 97, 83, 90, 97, 97, 79, 97, 25, 61, 91, 98, 61, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 34, 97, 97, 97, 97, 39, 87, 73, 76, 74, 97, 70, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 80, 83, 106, 103, 97, 97, 115, 97, 97, 97, 97, 97, 97, 97, 70, 65, 97, 97, 97, 97, 97, 97, 97, 67, 97, 97, 97, 97, 97, 97, 97, 97, 65, 86, 93])
    y = np.array([100, 100, 100, 99, 55, 67, 98, 99, 99, 97, 99, 101, 109, 99, 100, 99, 97, 102, 96, 99, 99, 98, 99, 99, 98, 99, 97, 97, 100, 99, 105, 100, 4, 99, 99, 97, 96, 97, 98, 99, 97, 94, 103, 99, 98, 97, 99, 98, 96, 98, 99, 96, 96, 99, 96, 99, 96, 100, 96, 13, 99, 110, 99, 97, 99, 99, 96, 98, 99, 97, 99, 97, 97, 96, 100, 9, 97, 115, 99, 115, 102, 98, 100, 99, 96, 99, 98, 99, 97, 99, 12, 97, 98, 99, 98, 98, 107, 109, 105, 114, 98, 99, 98, 99, 98, 100, 99, 99, 99, 99, 99, 98, 98, 99, 97, 99, 22, 115, 100, 100, 98, 99, 97, 99, 99, 99, 99, 100, 100, 105, 99, 99, 98, 97, 99, 102, 99, 100, 100, 98, 98, 97, 99, 99, 97, 99, 99, 97, 98, 107])
    yRA = np.array([100, 100, 100, 99, 77, 67, 82, 99, 99, 97, 98, 101, 109, 99, 99, 99, 97, 102, 96, 99, 99, 98, 99, 99, 98, 99, 97, 97, 100, 99, 105, 102, 4, 99, 99, 97, 96, 97, 97, 99, 98, 94, 98, 99, 98, 97, 99, 98, 96, 97, 99, 97, 97, 97, 96, 99, 96, 100, 96, 13, 56, 110, 99, 97, 99, 99, 97, 98, 99, 97, 98, 97, 97, 96, 100, 9, 53, 73, 99, 107, 102, 98, 100, 99, 96, 97, 98, 99, 97, 99, 12, 97, 98, 99, 98, 98, 102, 104, 104, 106, 98, 99, 98, 99, 98, 100, 99, 99, 99, 99, 99, 98, 98, 99, 98, 99, 60, 78, 84, 100, 99, 99, 97, 99, 99, 99, 99, 100, 100, 105, 99, 99, 98, 97, 99, 100, 99, 99, 100, 98, 98, 97, 98, 99, 98, 98, 99, 97, 98, 102])
    print("x, average = {}, standard deviation = {}, min = {}, max = {}".format(x.mean(), x.std(), min(x), max(x)))
    print("xRa, average = {}, standard deviation = {}, min = {}, max = {}".format(xRA.mean(), xRA.std(), min(xRA), max(xRA)))
    print("y, average = {}, standard deviation = {}, min = {}, max = {}".format(y.mean(), y.std(), min(y), max(y)))
    print("yRa, average = {}, standard deviation = {}, min = {}, max = {}".format(yRA.mean(), yRA.std(), min(yRA), max(yRA)))

if __name__ == "__main__":
    top_left()
    top_right()
    mid()
    bottom_left()
    bottom_right()
