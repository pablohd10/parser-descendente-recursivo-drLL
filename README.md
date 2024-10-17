# Proyecto: Parser Descendente Recursivo (drLL) en C

## 1. Descripción
Este proyecto implementa un parser descendente recursivo (drLL) en el lenguaje C, diseñado para procesar una gramática que representa operaciones matemáticas y el almacenamiento de variables en notación prefija.

### 1.1 Estructura de Archivos
- drLL.c: Código fuente que contiene la implementación del parser. El parser sigue un enfoque descenso-recursivo para procesar expresiones en notación prefija y realizar cálculos, además de almacenar valores en variables.
  
- drLL.pdf: Documento con la documentación detallada del proyecto. Incluye una explicación técnica sobre el funcionamiento del parser, la gramática utilizada y diagramas que ilustran el proceso de análisis sintáctico.
  
- drLL.txt: Archivo de texto con sentencias de prueba para testear el parser.
  
### 1.2 Gramática
La gramática utilizada en el parser incluye las siguientes operaciones y reglas:

Operaciones aritméticas básicas: suma, resta, multiplicación, y división.

Asignación de valores a variables.

Notación prefija: Las operaciones y los operandos siguen el formato donde el operador precede a sus operandos.
Por ejemplo:

(+ 5 3)       -> Resultado: 8

(- (* 3 4) 4)   -> Resultado: 8

( ! C 2 ) -> Resultado: 2

C -> Resultado: 2

## 2. Instrucciones de Uso
Compilación del Código: Para compilar el archivo drLL.c, puedes utilizar un compilador de C como gcc:

  ```bash
  gcc drLL.c -o drLL
  ```
Ejecución: Después de compilar el programa, puedes ejecutarlo para analizar expresiones matemáticas y realizar asignaciones:

  ```bash
  ./drLL
  ```
Introduce las expresiones en notación prefija, y el parser evaluará las operaciones o almacenará variables según sea necesario.

## 3. Contribuciones
Las contribuciones para mejorar el parser o agregar nuevas funcionalidades son bienvenidas. Si deseas participar, abre un issue o envía un pull request con tus mejoras.

