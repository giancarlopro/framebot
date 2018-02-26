Começando
=========

Framebot é uma biblioteca feita em C para facilitar o uso da BOT API do telegram.

Instalação
----------

Para instalar a biblioteca você deve primeiro clonar o nosso repositório:
    ``$ git clone https://github.com/giancarlopro/framebot``

Agora você vai precisar ter o `cmake` instalado, e algumas libs:
    ``$ sudo apt install cmake openssl curl jansson``

Após isso entre na pasta onde a biblioteca foi clonada, por padrão vai ser `framebot`:
    ``$ cd framebot``

Agora crie uma pasta para compilar a biblioteca e rode o cmake para criar o makefile:
    ``$ mkdir build``

    ``$ cd build``

    ``$ cmake ..``

Agora utilize o makefile para compilar e instalar a biblioteca:
    ``$ make``

    ``$ make install``

Utilização
----------

Para utilizar a biblioteca em seus projetos, você deve informar ao compilador explicitamente
as bibliotecas que serão compiladas juntas.

* Se estiver compilando pelo terminal:
    ``$ gcc projeto.c -o out -lcurl -ljansson -lframebot``

* Se estiver utilizando o cmake basta informar no seu CMakeLists.txt, em target_link_libraries:
    ``target_link_libraries(seuexecutavel framebot)``