#
def predict(row, weights):
    activation = weights[0]
    for i in range(len(row) - 1):               #obliczanie funkcji aktywacji
        activation += weights[i + 1] * row[i]
    return 1.0 if activation >= 0.0 else 0.0


# Obliczanie/trenowanie wag funkcji
def train_weights(train, l_rate, n_epoch):
    weights = [0.0 for i in range(len(train[0]))]
    for epoch in range(n_epoch):
        sum_error = 0.0
        for row in train:
            prediction = predict(row, weights)
            error = row[-1] - prediction
            sum_error += error ** 2
            weights[0] = weights[0] + l_rate * error
            for i in range(len(row) - 1):
                weights[i + 1] = weights[i + 1] + l_rate * error * row[i]
        print('>epoch=%d, lrate=%.3f, error=%.3f' % (epoch, l_rate, sum_error))
    return weights


# Dane
#funkcja której chcemy nauczyć
dataset = [[0, 0, 0],
           [0, 1, 1],
           [1, 0, 1],
           [1, 1, 1]
          ]
l_rate = 0.1            #współczynnik uczenia się
n_epoch = 10            #liczba epok

#drukowanie wyniku
weights = train_weights(dataset, l_rate, n_epoch)
