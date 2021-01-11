import os
os.environ['TF_CPP_MIN_LOG_LEVEL'] = '1'
import matplotlib.pyplot as plt
import time
import datetime
import tensorflow as tf
import keras
from keras.models import Sequential
from tensorflow.keras import datasets, layers, models


def load_dataset():
    (x_train, y_train), (x_test, y_test) = keras.datasets.cifar10.load_data()
    x_train = x_train.reshape(x_train.shape[0], 32 * 32 * 3).astype('float64')
    x_test = x_test.reshape(x_test.shape[0], 32 * 32 * 3).astype('float64')
    x_train = x_train / 255.0
    x_test = x_test / 255.0

    return x_train, y_train, x_test, y_test


def summarize(history):
    plt.title('Classification Accuracy')
    plt.plot(history.history['sparse_categorical_accuracy'], color='blue', label='train')
    plt.plot(history.history['val_sparse_categorical_accuracy'], color='orange', label='test')
    plt.xlabel('Epoch')
    plt.ylabel('Accuracy')
    plt.ylim([0.5, 1])
    plt.legend(loc='lower right')
    plt.autoscale()
    plt.show()


def define_model():
    # create model
    model = Sequential()
    model.add(layers.Dense(256, input_dim=3072, activation='sigmoid'))
    model.add(layers.Dense(128, activation='relu'))
    model.add(layers.Dense(64, activation='relu'))
    model.add(layers.Dense(32, activation='relu'))
    model.add(layers.Dense(16, activation='relu'))
    model.add(layers.Dense(10, activation='softmax'))

    # compile model
    opt = keras.optimizers.SGD(lr=0.05, momentum=0.01)
    model.compile(optimizer=opt, loss='sparse_categorical_crossentropy',
                  metrics=[tf.keras.metrics.sparse_categorical_accuracy])
    return model


def main():
    # START STATUS
    start = time.time()
    print(f"Run started on {datetime.datetime.now()}\n")

    # load dataset
    x_train, y_train, x_test, y_test = load_dataset()

    # define model
    model = define_model()

    # fit model
    history = model.fit(x_train, y_train, epochs=50, validation_data=(x_test, y_test), verbose=2)

    # evaluate model
    loss, acc = model.evaluate(x_test, y_test, verbose=1)

    # learning curves
    summarize(history)

    # FINAL STATUS
    end = time.time()
    print('Test accuracy > %.3f' % (acc * 100.0), "%")
    print(f"\nElapsed time: {end - start}s = {(end - start) / 60}min")
    print(f"Run finished at {datetime.datetime.now()}")


main()
