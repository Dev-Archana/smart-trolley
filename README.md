# smart-trolley
Below is a **complete, professional `README.md`** you can use **as-is** for your **Smart Trolley System (IoT + MERN)** project.
It explains **what the project is**, **how to download**, **configuration**, and **how to run end-to-end** — perfect for **GitHub + final-year submission**.

---

# 🛒 Smart Trolley System (IoT + MERN Stack)

A **Smart Trolley System** that uses **IoT (ESP32 + RFID)** integrated with the **MERN stack (MongoDB Atlas, Express, React, Node.js)** to automatically add/remove products, calculate bills, and display real-time cart data on a web dashboard.

---

## 📌 Features

* RFID-based **automatic product detection**
* Admin authentication using **RFID + keypad**
* Real-time **cart total calculation**
* **ESP32 → Node.js → MongoDB Atlas** integration
* Live **React dashboard**
* Secure cloud database (MongoDB Atlas)
* Modular and scalable architecture

---

## 🧠 System Architecture

```
ESP32 + RFID
     |
     | HTTP (JSON)
     v
Node.js + Express API
     |
     v
MongoDB Atlas (Cloud)
     |
     v
React + Vite Dashboard
```

---

## 🧰 Tech Stack

| Layer    | Technology                         |
| -------- | ---------------------------------- |
| IoT      | ESP32, RFID (MFRC522), LCD, Keypad |
| Backend  | Node.js, Express.js                |
| Database | MongoDB Atlas                      |
| Frontend | React + Vite                       |
| Protocol | HTTP REST (JSON)                   |

---

## 📁 Project Folder Structure

```
smart-trolley/
│
├── hardware/
│   └── esp32_smart_trolley.ino
│
├── backend/
│   ├── config/
│   │   └── db.js
│   ├── models/
│   │   ├── Product.js
│   │   └── CartEvent.js
│   ├── routes/
│   │   └── trolleyRoutes.js
│   ├── server.js
│   ├── package.json
│   └── .env.example
│
├── frontend/
│   ├── src/
│   │   ├── components/
│   │   │   ├── Cart.jsx
│   │   │   └── EventLog.jsx
│   │   ├── services/
│   │   │   └── api.js
│   │   ├── App.jsx
│   │   └── main.jsx
│   ├── index.html
│   └── package.json
│
├── .gitignore
└── README.md
```

---

## ⬇️ How to Download the Project

### Option 1: Clone from GitHub

```bash
git clone https://github.com/your-username/smart-trolley.git
cd smart-trolley
```

### Option 2: Download ZIP

1. Click **Code → Download ZIP**
2. Extract the folder
3. Open in **VS Code**

---

## 🔧 Configuration (IMPORTANT)

### 1️⃣ MongoDB Atlas Setup

1. Create an account at:
   👉 [https://www.mongodb.com/atlas](https://www.mongodb.com/atlas)
2. Create a **Cluster**
3. Create a **Database User**
4. Whitelist IP:

   ```
   0.0.0.0/0
   ```

---

### 2️⃣ Backend Environment Variables

Create `.env` file inside `backend/`

```env
MONGO_URI=mongodb+srv://USERNAME:PASSWORD@cluster0.mongodb.net/smart_trolley
PORT=5000
```

⚠️ Replace `USERNAME`, `PASSWORD`, and cluster URL.

---

### 3️⃣ ESP32 Configuration

Update WiFi and server IP:

```cpp
const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";

const char* serverURL = "http://YOUR_PC_IP:5000/api/trolley/event";
```

💡 Example:

```
http://192.168.1.100:5000/api/trolley/event
```

---

## ▶️ How to Run the Project (End-to-End)

### 🔹 Step 1: Start Backend Server

```bash
cd backend
npm install
node server.js
```

Expected output:

```
MongoDB Atlas Connected
Server running on port 5000
```

---

### 🔹 Step 2: Start Frontend (React + Vite)

```bash
cd frontend
npm install
npm run dev
```

Open browser:

```
http://localhost:5173
```

---

### 🔹 Step 3: Upload ESP32 Code

1. Open `hardware/esp32_smart_trolley.ino` in Arduino IDE
2. Select correct **Board** and **Port**
3. Upload code
4. Power ESP32 and start scanning RFID cards

---

## 📊 How It Works

1. Admin scans RFID card → trolley unlocks
2. Product RFID scanned → added/removed
3. ESP32 sends JSON data to backend
4. Backend saves data in MongoDB Atlas
5. React dashboard displays live updates

---

## 🔐 Security Notes

* `.env` file is ignored using `.gitignore`
* MongoDB Atlas credentials are not exposed
* Backend CORS enabled for local development

---

## 🧪 Sample API Payload (ESP32 → Backend)

```json
{
  "product": "Dairy Milk",
  "price": 40,
  "event": "ADDED",
  "total": 120
}
```

---

## 🚀 Future Enhancements

* WebSocket real-time updates
* Multiple trolley support
* Weight sensor fraud detection
* Admin analytics dashboard
* Online payment integration
* Cloud deployment

---

## 🎓 Academic Use

This project is suitable for:

* Final Year Engineering Project
* IoT + Web Development Demonstration
* Smart Retail / Smart Shopping Research

---

