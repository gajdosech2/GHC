class Pizza:
    def __init__(self):
        self.P = []
        self.rowCount = self.columnCount = self.minIngredient = self.maxArea = 0

    def load(self, fileName):
        with open(fileName) as f:
            self.rowCount, self.columnCount, self.minIngredient, self.maxArea = tuple(map(int, f.readline().split()))
            for i in range(self.rowCount):
                self.P.append(f.readline().rstrip())

    def solve(self):
        results = []
        for r in range(self.rowCount):
            beg = 0
            end = 0
            mushroomCount = 0
            tomatoCount = 0
            while end < self.columnCount:
                if self.P[r][end] == 'T':
                    tomatoCount += 1
                elif self.P[r][end] == 'M':
                    mushroomCount += 1
                end += 1

                if end - beg > self.maxArea:
                    if self.P[r][beg] == 'T':
                        tomatoCount -= 1
                    elif self.P[r][beg] == 'M':
                        mushroomCount -= 1
                    beg -= 1

                if end - beg <= self.maxArea and mushroomCount >= self.minIngredient and tomatoCount >= self.minIngredient:
                    results.append((r, beg, r, end-1))
                    beg = end
                    mushroomCount = 0
                    tomatoCount = 0
        self.save(results)
        

    def save(self, results):
        with open("pizza.out", "w") as w:
            print(len(results), file=w)
            for s in results:
                r = str(s[0]) + " " + str(s[1]) + " " + str(s[2]) + " " + str(s[3])
                print(r, file=w)

    def printPizza(self):
        for i in range(self.rowCount):
            for j in range(self.columnCount):
                print(self.P[i][j], end="")
            print()

p = Pizza()
p.load("a_example.in")
