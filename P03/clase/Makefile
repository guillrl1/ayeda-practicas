# Variables de compilación
CXX = g++-14
CXXFLAGS = -std=c++20 
SRC_DIR = src
TARGET = P03_calc

# Archivos fuente
SOURCES = $(wildcard $(SRC_DIR)/*.cc)
OBJECTS = $(SOURCES:.cc=.o)

# Regla por defecto
all: $(TARGET)

# Regla para crear el binario final
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Regla para compilar los archivos fuente en objetos
%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpiar archivos generados
clean:
	rm -f $(SRC_DIR)/*.o $(TARGET)

# Reglas adicionales
.PHONY: all clean