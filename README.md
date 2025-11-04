# 🧠 Perceptron M/F in C

A simple **perceptron** written in **C** that learns to predict whether a person is **male or female** based on three features:
- **Weight**
- **Age**
- **Height**

This project was built to **understand how a neural network works internally**, without relying on any machine learning libraries.

---

## 📦 Project Structure

```
percetron-mf/
├── dataset.txt        # Training dataset (weight, age, height, label)
├── weights.txt        # Saved weights after training
├── train.c            # Program to train the perceptron
├── predict.c          # Program to predict gender using trained weights
├── generate_dataset.c # (optional) Generates a realistic synthetic dataset
```

---

## ⚙️ How It Works

1. **Training**
   - The perceptron is trained using gradient descent and a sigmoid activation function.
   - It adjusts weights (`w1, w2, w3`) and bias (`b`) to minimize classification error.

2. **Prediction**
   - Once trained, it reads the `weights.txt` file and predicts a value between `0` and `1`:
     - `≈0` → Female  
     - `≈1` → Male

---

## 🧮 Math Behind

The perceptron computes:
```
z = w1*x1 + w2*x2 + w3*x3 + b
y = 1 / (1 + exp(-z))
```

Weights are updated by:
```
w_i += learning_rate * (y_true - y_pred) * x_i
b   += learning_rate * (y_true - y_pred)
```

---

## 🚀 Compilation & Usage

### 1️⃣ Compile the training program
```bash
gcc train.c -o train -lm
```

### 2️⃣ Train the model
```bash
./train
```

### 3️⃣ Predict using trained weights
```bash
gcc predict.c -o predict -lm
./predict 62 14 170
```

Example output:
```
Input: 62kg, 14y, 170cm → Predicted: Female (0.23)
```

---

## 🧠 Learning Objectives

✅ Understand the fundamentals of perceptrons  
✅ Implement gradient descent manually  
✅ Read and write model weights to files  
✅ See how numerical precision (double vs long double) affects convergence  

---

## 📈 Possible Improvements (Level 2)

- Add a **hidden layer** → turn it into a simple **MLP (Multi-Layer Perceptron)**
- Normalize input features to [0,1]
- Add plotting of error over epochs
- Implement training resume from `weights.txt`
- Experiment with different learning rates

---

## 🧑‍💻 Author

Developed by Liam 
For educational and demonstration purposes.  
Licensed under the MIT License.
