

# 🛍️ E-commerce Product Management System
## 📌 Overview
This is a console-based E-commerce Product Management System built in C++ using Object-Oriented Programming (OOP). It allows users to manage products, add items to a shopping cart, apply discounts, and perform checkout operations.

The system demonstrates key OOP principles:

✅ Classes & Objects

✅ Inheritance

✅ Encapsulation

✅ Polymorphism

✅ Operator Overloading

✅ Template Classes

✅ Abstract Interfaces

## ⚙️ Features
Product Management: Add regular products and electronics with warranty.

Shopping Cart: Add multiple products at once, view cart contents, apply discounts.

Checkout: Choose payment method (Cash or Card) and confirm purchase.

Interface: Discountable abstract class implemented by Product and ShoppingCart.

Template Class: InventoryList<T> for managing collections of products.

Operator Overloading:

+= to add products to cart.

== to compare products by ID.

## 🧠 Technologies Used
Language: C++11

Compiler: g++

Paradigm: Object-Oriented Programming

Data Structures: vector, map, pair, template, abstract class

## 📂 Project Structure
Mã
├── main.cpp          // Full source code
├── README.md         // Project documentation
├── Report.pdf        // OOA analysis, design explanation, UML diagrams (optional)
## 🚀 How to Build & Run
### On Linux / macOS / WSL:
```bash
g++ -std=c++17 main.cpp -o ecommerce
./ecommerce
```
### On Windows (MinGW):
```bash
g++ -std=c++17 main.cpp -o ecommerce.exe
ecommerce.exe
```
## 🧪 Sample Usage
Mã
===== MENU =====
1. Add Product
2. Add Electronics
3. Show Inventory
4. Add Items to Cart
5. Show Cart
6. Apply Discount
7. Checkout
8. Exit
Example input:
```bash
Enter Product IDs to add to cart (separated by space): P001 P002 P003
```
## 🤖 AI Disclosure
Author: Nguyen Minh Thanh – Student ID: 24110132

I used Microsoft Copilot to assist with:

Designing class structure and method organization

Implementing template and abstract classes

Improving code readability and OOP compliance

All code was written, tested, and customized by me. The AI was used ethically as a support tool, not for full code generation.

## 📝 Reflection
This project helped me solidify my understanding of OOP in C++. I learned how to:

Use inheritance to extend base functionality

Apply polymorphism through virtual and overridden methods

Manage relationships between objects (e.g., cart and inventory)

Use templates and interfaces to build flexible, reusable components

One challenge was handling multiple product additions and ensuring stock consistency. I overcame this by using structured input parsing and encapsulating logic within classes.

## 📎 Future Improvements
Add persistent storage (save/load from file)

Implement order history and receipts

Add user authentication

Support quantity input per product (e.g., P001:2 P002:1)
