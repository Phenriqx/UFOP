
build:
	g++ src\\*.cpp src\\moduloDoMeuApp\\*.cpp -o bin\\app
	
run: 
	bin\app

build_unit:
	g++ test\\unit\\*.cpp src\\moduloDoMeuApp\\*.cpp -o bin\\unit_testes

run_unit: build_unit
	bin\unit_testes
 
build_func:
	g++ test\\func\\*.cpp src\\moduloDoMeuApp\\*.cpp -o bin\\func_testes

run_func:build_func
	bin\func_testes

build_dll:
	g++ -shared src\\moduloDoMeuApp\\*.cpp -o lib\\modulo.dll
	
build_dll_app: build_dll
	g++ src\\*.cpp -L.\lib -lmodulo -o .\bin\app.exe
	
clean: 
	del .\bin\*.exe
	del .\bin\*.dll
	del .\lib\*.dll
	
	
	