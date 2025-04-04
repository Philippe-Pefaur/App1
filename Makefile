# Variables
CC = gcc                      # Compilador
CFLAGS = -std=c99 -Wall -Wextra  # Opciones de compilación
TARGET = app1                 # Nombre del ejecutable
SOURCES = main.c utils.c metrics.c  # Archivos fuente
HEADERS = data_structures.h utils.h metrics.h  # Archivos de cabecera
OBJECTS = $(SOURCES:.c=.o)    # Archivos objeto generados a partir de los fuentes

# Regla principal: compilar el ejecutable
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)

# Regla para compilar archivos .c en .o
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Regla para limpiar archivos generados
clean:
	del /Q $(OBJECTS) $(TARGET)