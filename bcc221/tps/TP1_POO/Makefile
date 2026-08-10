
# Nome do compilador
CXX = g++

# Opções de compilação (avisos ativados e padrão C++17)
CXXFLAGS = -Wall -std=c++17 -g

# Nome do executável final
TARGET = banco

# Lista de todos os ficheiros fonte (.cpp)
SRCS = main.cpp auxiliares.cpp cliente.cpp credito.cpp gerente.cpp pessoa.cpp transacao.cpp

# Lista de ficheiros objeto (substitui a extensão .cpp por .o)
OBJS = $(SRCS:.cpp=.o)

# Regra principal (executada ao digitar apenas 'make')
all: $(TARGET)

# Regra para compilar o executável final juntando todos os objetos (.o)
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)
	@echo "Compilação concluída com sucesso! Executável '$(TARGET)' gerado."

# Regra genérica para compilar cada .cpp no seu respetivo .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Regra para limpar os ficheiros gerados (.o e o executável)
clean:
	rm -f $(OBJS) $(TARGET)
	@echo "Ficheiros de compilação removidos."

# Regra para executar o programa rapidamente
run: $(TARGET)
	./$(TARGET)