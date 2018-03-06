Tutorial
========

Neste pequeno tutorial, vamos criar um echo bot.
Ele basicamente vai reenviar as mensagens que são recebidas como resposta.

O código está disponível em `GitHub: Echo Bot`_.

.. _`GitHub: Echo Bot`: https://github.com/giancarlopro/framebot/blob/master/examples/echo.c

Estrutura básica
----------------

Para este projeto, nós vamos receber o `token` do bot na chama do binário, ficando assim:

.. code-block:: shell

   ./bot TOKEN

Para isso vamos criar nossa estrutura em c da seguinte forma:

.. code-block:: c

   #include <stdio.h>
   #include <framebot/framebot.h>

   int main (int argc, char **argv) {
      if (argc < 2) {
         printf("Usage: ./echo BOT_TOKEN\n");
         exit(-1);
      }

      framebot_init(); // Inicializamos

      return 0;
   }

Aqui nós criamos uma condição caso o `token` não seja fornecido, 
e inicializamos a biblioteca com a função :c:func:`framebot_init`.

Agora precisaremos de algumas variáveis para manipular a biblioteca.
Serão elas:

.. code-block:: c

   long int last_offset = 0;
   Bot *echo;
   Framebot *frame_update;
   Update *message, *temp;

Onde:
   :c:data:`last_offset` vai ser utilizado para podermos resetar a lista de updates mais tarde
   
   :c:data:`echo` é o nosso objeto do tipo :c:type:`Bot`, essencial para manipular a biblioteca
   
   :c:data:`frame_update` que vai ser inicializado pela função :c:func:`get_updates` com as ultimas mensagens
   
   :c:data:`message` que vai conter nosso array de mensagens