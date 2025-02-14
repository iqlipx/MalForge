# **MalForge – ELF Binary Modification Tool**

MalForge is a tool designed to manipulate and corrupt ELF binaries, making reverse engineering and binary analysis more challenging. The tool provides multiple corruption techniques, including header modification, symbol table obfuscation, and the addition of decoy sections.

---

## **Table of Contents**

1. [Features](#features)  
2. [Installation](#installation)  
3. [Usage](#usage)  
4. [How It Works](#how-it-works)  
   - [1. ELF Header Corruption](#elf-header-corruption)  
   - [2. Section Header Overwriting](#section-header-overwriting)  
   - [3. Symbol Table Obfuscation](#symbol-table-obfuscation)  
   - [4. Decoy Section Addition](#decoy-section-addition)  
5. [Disclaimer](#disclaimer)
6. [Screenshots](#screenshots)

---

## **Features**

1. **ELF Header Corruption**  
   - Randomly modifies ELF magic bytes and nullifies the section header offset to hinder ELF analysis tools.
  
2. **Section Header Overwriting**  
   - Overwrites random chunks of the section headers to confuse disassemblers and debuggers.

3. **Symbol Table Obfuscation**  
   - Uses XOR encryption to obfuscate the symbol table, preventing extraction of function names and variable identifiers.

4. **Decoy Section Addition**  
   - Adds a new section filled with random junk data to mislead reverse engineers.

---

## **Installation**

1. **Prerequisites:**  
   - GCC (GNU Compiler Collection) installed on your system.  
   - An ELF binary to modify.

2. **Compilation:**  
   Compile MalForge using the following command:

   ```bash
   gcc -o malforge malforge.c
   ```

## Usage
To run MalForge, provide the path to an ELF binary as an argument:

```bash
./malforge <elf_binary>
```

**Example**

```bash
./malforge test101
```
This command will apply all the corruption techniques to the provided ELF binary.


## How It Works
1. **ELF Header Corruption**
MalForge modifies the ELF header by:

- Changing the ELF magic bytes to random values.
- Nullifying the section header table offset.
- This makes the binary harder to parse by tools that rely on the ELF format.

2. **Section Header Overwriting**
The section headers are partially overwritten with random bytes, rendering the sections unidentifiable and breaking tools that rely on these headers.

3. **Symbol Table Obfuscation**
The `.symtab` section, which contains the binary’s symbol information, is XOR-encrypted with a key. This prevents reverse engineers from easily accessing function and variable names.

4. **Decoy Section Addition**
A decoy section filled with random junk data is added to the binary at an arbitrary offset. This can mislead reverse engineers and make binary analysis more confusing.


## Screenshots

![test](/images/test.png)

![elf](/images/elf.png)

![corrupt](/images/corrupt.png)

![result](/images/result.png)

[HexDump](hexdump)

## Disclaimer
MalForge is intended for educational and research purposes only. Unauthorized modification of binaries is illegal in many jurisdictions. Use this tool responsibly and ensure that you have permission before modifying any binary files.


