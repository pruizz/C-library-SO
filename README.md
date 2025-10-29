# Práctica 1 – Sistemas Operativos  
## Programación en C – Curso 2025/26  

### 📘 Descripción general

Esta práctica consiste en la implementación de una **biblioteca en lenguaje C** que proporcione tres funciones principales (`head`, `tail` y `longlines`) para trabajar con líneas de texto recibidas desde la entrada estándar.  
El objetivo es simular el comportamiento de los comandos **`head(1)`** y **`tail(1)`**, además de incluir una función adicional que muestre las **líneas más largas** de la entrada.

El proyecto está compuesto por tres archivos fuente y un script de compilación:

- `libreria.c` → Implementación de las funciones `head`, `tail` y `longlines`.  
- `test.c` → Programa principal de prueba que invoca las funciones de la biblioteca.  
- `compila.sh` → Script que genera la librería estática `liblibreria.a` y compila el programa de prueba.  

El archivo de cabeceras `libreria.h` es proporcionado por el profesorado y **no debe modificarse**.

---

### 🧩 Funciones implementadas

#### `int head(int N)`
Muestra las **N primeras líneas** leídas desde la entrada estándar, imitando el comportamiento del comando `head`.  
Si hay menos de N líneas disponibles, muestra todas las líneas.

#### `int tail(int N)`
Muestra las **N últimas líneas** de la entrada estándar.  
Lee todas las líneas y conserva en memoria únicamente las N más recientes, haciendo uso de memoria dinámica.

#### `int longlines(int N)`
Muestra las **N líneas más largas** de la entrada estándar, ordenadas de mayor a menor longitud.  
Si hay menos de N líneas, las muestra todas.

---

### ⚙️ Compilación y ejecución

Para compilar y generar el ejecutable, basta con ejecutar el script `compila.sh`:

```bash
./compila.sh
