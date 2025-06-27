const express = require("express");
const multer = require("multer");
const path = require("path");
const { execFile } = require("child_process");

const app = express();
const PORT = 9000;

// Set up multer
const upload = multer({ dest: "uploads/" });

// Path to the Huffman executable
const huffmanPath = path.resolve(__dirname, "../compressor/huffman.exe");

app.get('/', (req,res)=>{
    res.send("HI");
})

// Compression Route
app.post("/api/compress", upload.single("file"), (req, res) => {
  const inputPath = req.file.path;
  const outputPath = inputPath + ".huff";

  execFile(huffmanPath, [inputPath, outputPath], (err, stdout, stderr) => {
    if (err) {
      console.error("Compression failed:", err);
      return res.status(500).json({ error: "Compression failed" });
    }

    res.json({
      message: "Compression successful",
      compressedFile: outputPath,
    });
  });
});

// Start server
app.listen(PORT, () => {
  console.log(`Server running on port ${PORT}`);
});
