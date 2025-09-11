
---

# 🔐 RC4 Encryption/Decryption Program

A simple implementation of the **RC4 stream cipher** for encryption and decryption of files using a given key.

---

## 🛠️ Compilation

To compile the program, use:

```bash
gcc -std=c99 -Wall -Wextra -pedantic -Wno-unused-parameter -o RC4 main.c
```
---

## 🚀 Usage

Run the program with:

```bash
./RC4 -h
```

This will print the manual and usage information.

### 📖 Command-Line Syntax

```bash
Usage: ./RC4 -k <key> -i <input_file> -o <output_file>
```

**Arguments:**

* `-k` — Key used for encryption/decryption (e.g., `mysecret`)
* `-i` — Input file name (e.g., `input.txt`)
* `-o` — Output file name (e.g., `output.txt`)

> 📌 Files should be in the same directory as the program (like `main.c`), unless full paths are specified.

### Notes

* All input must be provided via **command-line arguments**

* There is **no interactive input**

* If the program finishes successfully, it prints:

  ```
  End of file reached
  ```

* If incorrect input is provided:

  * The manual will be displayed
  * The invalid values will be echoed back

---

## 📄 File Handling

* The input and output text files must **exist beforehand** and be correctly prepared
* The program **does not check**:

  * Whether the input file is empty
  * Whether the output file is writable or non-empty

---

## ✅ Features Completed

* [x] Generation and initialization of the `S[256]` array
* [x] Key-based scrambling using `swap_elements()` (Key Scheduling Algorithm)
* [x] Generation of keystream and XOR-based transformation (Pseudo-Random Generation Algorithm)
* [x] File input and output handling
* [x] Command-line interface using `getopt`
* [x] Full encryption/decryption based on specification
* [x] Manual/help output for incorrect usage

---

## 🧪 Tested Environment

* ✅ Built and tested on **Linux Mint**
* ❌ Not tested on other platforms

---

## 📌 Example: Encrypting and Decrypting Files

### 🔒 Encrypt

```bash
./RC4 -k mykey -i input.txt -o encrypted.txt
```

### 🔓 Decrypt

```bash
./RC4 -k mykey -i encrypted.txt -o output.txt
```

If the same key is used, `output.txt` should match the original `input.txt`.

---