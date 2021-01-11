# Load OpenAI Gym and other necessary packages
import gym
import random
import numpy as np
import time
from IPython.display import clear_output


def main():
    # Environment
    env = gym.make("Taxi-v3")

    # Training parameters for Q learning
    alpha = 0.1  # Learning rate
    gamma = 0.6  # Future reward discount factor
    epsilon = 0.1  # Decision boundary for learning
    num_of_episodes = 10000  # How many different starts

    # Q tables for rewards
    q_reward = -1*np.ones([env.observation_space.n, env.action_space.n])

    # Training w/ random sampling of actions
    for i in range(1, num_of_episodes):
        state = env.reset()
        epochs, reward, = 0, 0
        done = False

        while not done:
            if random.uniform(0, 1) < epsilon:
                action = env.action_space.sample()  # Explore action space
            else:
                action = np.argmax(q_reward[state])  # Exploit learned values

            next_state, reward, done, info = env.step(action)

            old_value = q_reward[state, action]
            next_max = np.max(q_reward[next_state])

            new_value = (1 - alpha) * old_value + alpha * (reward + gamma * next_max)
            q_reward[state, action] = new_value

            state = next_state
            epochs += 1

        if i % 100 == 0:
            clear_output(wait=True)
            print(f"Episode: {i}/{num_of_episodes}")

    print("\nTraining finished.\n")

    # Test drive (optional)
    num_of_drives = int(input("How many test drives would you like to be drawn (0-n): "))
    for k in range(num_of_drives):
        state = env.reset()
        tot_reward = 0
        for t in range(40):
            action = np.argmax(q_reward[state, :])
            state, reward, done, info = env.step(action)
            tot_reward += reward
            env.render()
            time.sleep(1)
            if done:
                print("Total reward %d" % tot_reward)
                break
    print("\nTesting finished.\n")

    # Testing with 10 episodes to calculate average total reward and average number of steps.
    # In case of the car still gets stuck the reward can be negative and number of actions is high.
    # Otherwise rewards should be 10 +- 5 and steps around 10-20.
    total_rewards, total_epochs = 0, 0
    for i in range(10):
        state = env.reset()
        epochs, reward, = 0, 0
        done = False

        while not done:
            action = np.argmax(q_reward[state])
            state, reward, done, info = env.step(action)
            epochs += 1
            total_rewards += reward
        total_epochs += epochs

    print(f"Results after 10 episodes:")
    print(f"Average total reward: {total_rewards / 10}")
    print(f"Average number of actions: {total_epochs / 10}")


main()
