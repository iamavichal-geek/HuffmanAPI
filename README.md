#  CodeZip - File Compression API using C++ (Huffman) + Node.js

**CodeZip** is a hybrid full-stack project that enables efficient file compression using the **Huffman Coding algorithm** implemented in **C++**, served through a **Node.js Express API**. It allows users to upload files for compression and returns the compressed `.huff` output file.

>  Ideal for demonstrating knowledge of C++, backend system design, and full-stack integration during interviews.

---

##  Tech Stack

-  **C++** — Huffman compression logic
-  **Node.js + Express.js** — REST API server
-  **Multer** — File upload handling
-  **child_process.execFile** — Bridge between Node.js and compiled C++ binaries
-  **PostgreSQL** or **MongoDB (optional)** — Extendable for logging/compression stats

---

##  Features

- Compress any file (text, log, etc.) via API
- Uses **Huffman coding** for efficient compression
- Clean separation of **backend** and **compression logic**
- Easily extendable to add decompression, file download, auth, or dashboard

---

##  Folder Structure
CodeZip/
├── backend/
│ ├── index.js # Express server
│ ├── package.json
│ └── uploads/ # Temp uploaded + compressed files
├── compressor/
│ ├── huffman.cpp # Huffman compression logic
│ ├── decompressor.cpp # (Optional) Decompression logic
│ └── huffman.exe # Compiled binary


---

## ⚙️ Local Setup

### 1. Clone the Repo

```bash
git clone https://github.com/your-username/CodeZip.git
cd CodeZip


2. Compile the C++ Huffman Program
bash
Copy
Edit
cd compressor
g++ huffman.cpp -o huffman.exe
⚠ This will generate a binary named huffman.exe — ensure you’re using g++ or MinGW on Windows.

3. Start Backend Server
bash
Copy
Edit
cd ../backend
npm install
node index.js
This runs the Express.js server on http://localhost:9000.

 API Usage
 POST /compress
URL: http://localhost:9000/compress
Form Data: file (type: File)

▶ Sample (Postman):
Method: POST

Body → form-data:

Key: file | Type: File | Value: yourfile.txt

 Success Response:
json
Copy
Edit
{
  "message": "Compression successful",
  "output": "uploads/filename.huff"
}
