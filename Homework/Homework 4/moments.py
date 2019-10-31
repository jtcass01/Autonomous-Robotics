import numpy as np

class Moment():
    class Area(object):
        def __init__(self, image):
            self.image = image
            self.area = Moment.Area.calculate_area(image)

        def __str__(self):
            return "The of the image area is " + str(self.area)

        @staticmethod
        def calculate_area(image):
            area = 0

            for row in image:
                for value in row:
                    area += value

            return area


    class CenterOfMass(object):
        def __init__(self, image):
            self.image = image
            self.x_bar = Moment.CenterOfMass.calculate_x_bar(image)
            self.y_bar = Moment.CenterOfMass.calculate_y_bar(image)

        def __str__(self):
            return "The of the center of mass area is (" + str(self.x_bar) + ", " + str(self.y_bar) + ")"

        @staticmethod
        def calculate_x_bar(image):
            x_bar = 0
            area = Moment.Area.calculate_area(image)

            for y, row in enumerate(image):
                for x, value in enumerate(row):
                    x_bar += x * value

            return x_bar / area

        @staticmethod
        def calculate_y_bar(image):
            y_bar = 0
            area = Moment.Area.calculate_area(image)

            for y, row in enumerate(image):
                for x, value in enumerate(row):
                    y_bar += y * value

            return y_bar / area

    class Orientation(object):
        def __init__(self, image):
            self.image = image
            self.mxx = Moment.Orientation.calculate_mxx(image)
            self.myy = Moment.Orientation.calculate_myy(image)
            self.mxy = Moment.Orientation.calculate_mxy(image)
            self.theta = Moment.Orientation.calculate_theta(image)

        def __str__(self):
            return "(mxx: " + str(self.mxx) + ", myy: " + str(self.myy) + ", mxy: " + str(self.mxy) + ", theta: " + str(self.theta) + ")"

        @staticmethod
        def calculate_mxx(image):
            mxx = 0
            x_bar = Moment.CenterOfMass.calculate_x_bar(image)

            for y, row in enumerate(image):
                for x, value in enumerate(row):
                    mxx += (x-x_bar)**2 * value

            return mxx

        @staticmethod
        def calculate_myy(image):
            myy = 0
            y_bar = Moment.CenterOfMass.calculate_y_bar(image)

            for y, row in enumerate(image):
                for x, value in enumerate(row):
                    myy += (y-y_bar)**2 * value

            return myy

        @staticmethod
        def calculate_mxy(image):
            mxy = 0
            x_bar = Moment.CenterOfMass.calculate_x_bar(image)
            y_bar = Moment.CenterOfMass.calculate_y_bar(image)

            for y, row in enumerate(image):
                for x, value in enumerate(row):
                    mxy += 2 * ( y - y_bar ) * ( x - x_bar ) * value

            return mxy

        @staticmethod
        def calculate_theta(image):
            mxx = Moment.Orientation.calculate_mxx(image)
            myy = Moment.Orientation.calculate_myy(image)
            mxy = Moment.Orientation.calculate_mxy(image)

            return np.arctan((mxx - myy + ((mxx - myy)**2 + mxy**2)**0.5) / mxy)

if __name__ == "__main__":
    problem_4 = [
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 1, 0, 0, 0, 0, 1, 1],
        [0, 0, 0, 1, 0, 0, 0, 0, 1, 1],
        [0, 0, 0, 1, 1, 1, 0, 1, 1, 0],
        [0, 0, 0, 0, 0, 1, 1, 1, 0, 0],
        [0, 0, 0, 0, 0, 0, 1, 1, 0, 0],
        [0, 0, 0, 0, 0, 0, 1, 1, 0, 0],
        [0, 0, 0, 0, 0, 0, 1, 1, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
    ]

    notes_example = [
        [0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 1, 1, 0, 0, 0, 0, 0, 0],
        [0, 1, 1, 0, 0, 0, 0, 0, 0],
        [0, 1, 1, 0, 0, 0, 0, 0, 0],
        [0, 1, 1, 1, 1, 1, 1, 1, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0],
    ]

    examples = [problem_4, notes_example]

    for example in examples:
        moments = [Moment.Area(example), Moment.CenterOfMass(example), Moment.Orientation(example)]

        for moment in moments:
            print(moment)
