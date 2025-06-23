import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns
from scipy import stats
import random

# Seed for reproducibility
# np.random.seed(42)

# --- Option 1: Mixture of Two Normal Distributions ---

def generate_mixture_normals(n=66):
    # Define parameters
    mu1, sigma1, weight1 = 1.8, 0.2, 0.4
    mu2, sigma2, weight2 = 3.2, 0.5, 0.6

    sigma1 *= 8
    sigma2 *= 8

    # Generate number of samples for each component
    n1 = int(n * weight1)
    n2 = n - n1

    data1 = np.random.normal(mu1, sigma1, n1)
    data2 = np.random.normal(mu2, sigma2, n2)

    return np.concatenate([data1, data2])

# --- Option 2: Log-Normal Distribution (alternative) ---

def generate_lognormal(n=66):
    mu, sigma = 1.0, 0.5  # log-space parameters
    return np.random.lognormal(mean=mu, sigma=sigma, size=n)

# --- Choose one ---

# --- Plot ---
# sns.histplot(data, kde=True, bins=20, color='skyblue', edgecolor='black')
# plt.title("Synthetic Data Distribution")
# plt.xlabel("Value")
# plt.ylabel("Frequency")
# plt.grid(True)
# plt.show()

# # --- Optional: Print basic stats ---
# print("Min:", np.min(data))
# print("Max:", np.max(data))
# print("Mean:", np.mean(data))
# print("Std Dev:", np.std(data))

a = []

for q in range(16):
    data = generate_mixture_normals(1024)  # or: data = generate_lognormal()
    s = sum(data)
    # s = s + random.random() * 60 + random.random() * 60 + random.random() * 4
    s = round(s)
    a.append(s)
    print(s)

print()
print(round(np.mean(a)))
print(round(np.std(a)))
