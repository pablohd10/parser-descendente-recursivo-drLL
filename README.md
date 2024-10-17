# Proyecto: Parser Descendente Recursivo (drLL) en C

## Descripción
Este proyecto implementa un parser descendente recursivo (drLL) en el lenguaje C, diseñado para procesar una gramática que representa operaciones matemáticas y el almacenamiento de variables en notación prefija.

### Estructura de Archivos
- drLL.c: Código fuente que contiene la implementación del parser. El parser sigue un enfoque descenso-recursivo para procesar expresiones en notación prefija y realizar cálculos, además de almacenar valores en variables.
  
- drLL.pdf: Documento con la documentación detallada del proyecto. Incluye una explicación técnica sobre el funcionamiento del parser, la gramática utilizada y diagramas que ilustran el proceso de análisis sintáctico.
  
- drLL.txt: Archivo de texto con sentencias de prueba para testear el parser.
  
### Gramática
La gramática utilizada en el parser incluye las siguientes operaciones y reglas:

Operaciones aritméticas básicas: suma, resta, multiplicación, y división.
Asignación de valores a variables.
Notación prefija: Las operaciones y los operandos siguen el formato donde el operador precede a sus operandos.
Por ejemplo:

+ 5 3       -> Resultado: 8
* 2 + 1 3   -> Resultado: 8
= x 10      -> Asigna 10 a la variable x
Instrucciones de Uso
Compilación del Código: Para compilar el archivo drLL.c, puedes utilizar un compilador de C como gcc:

bash
Copiar código
gcc drLL.c -o drLL
Ejecución: Después de compilar el programa, puedes ejecutarlo para analizar expresiones matemáticas y realizar asignaciones:

bash
Copiar código
./drLL
Introduce las expresiones en notación prefija, y el parser evaluará las operaciones o almacenará variables según sea necesario.

Ejemplo de Entrada:

bash
Copiar código
./drLL
Input: + 7 * 2 3
Output: 13
Requisitos
Compilador de C (e.g., gcc).
Un sistema compatible con C que permita la compilación y ejecución de programas.
Contribuciones
Las contribuciones para mejorar el parser o agregar nuevas funcionalidades son bienvenidas. Si deseas participar, abre un issue o envía un pull request con tus mejoras.

