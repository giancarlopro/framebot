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

Variaveis
---------

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

Agora vamos inicializar nosso objeto :c:type:`Bot` para podermos usar a API do Telegram.
Para isso utilizamos a função :c:func:`framebot`, caso aconteça algum erro, ela retornará :c:type:`NULL`.
Vamos passar para a função nosso token que está localizado em :c:data:`argv[1]`.

.. code-block:: c
   
   echo = framebot(argv[1]);

Pegando atualizações
--------------------

Agora já podemos pegar as atualizações direto da API.

.. code-block:: c

   frame_update = get_updates(echo, NULL, last_offset, 100, 0, NULL);
   message = frame_update->update_message;
   temp = message;

Na primeira linha é retornado um objeto do tipo :c:type:`Framebot`, 
que contem referencias para as atualizações de diferentes tipos.
Na segunda linha nós armazenamos na variavel :c:data:`message` os updates 
do tipo `Message`_.
Na ultima linhas nós passamos a referencia do primeiro Update pra variavel :c:data:`temp`,
que nós vamos utilizar para iterar os Updates.

.. _`Message`: https://core.telegram.org/bots/api#update

Respondendo as mensagens
------------------------

Com as atualizações da API em mãos, agora vamos responder as mensagens recebidas pelo bot.
Primeiro vamos iterar nossos Updates, e responder com a mesma mensagem recebida.

.. code-block:: c

   while (temp) {
      if (temp->message) {
         if (send_message_chat (echo, temp->message->from->id, temp->message->text, NULL, 0, 0, temp->message->message_id, NULL)) {
            printf("Sended: \"%s\" to %s!\n", temp->message->text, temp->message->from->username);
         }
      }

      last_offset = temp->update_id + 1; // Aqui armazenamos o offset do ultimo update, para podermos resetar depois
      temp = temp->next;
   }

Aqui temos um while para iterar nossos Updates. Primeiro verificamos se recebemos de fato alguma mensagem,
depois tentamos enviar nossa resposta, caso consigamos é escrito na tela uma mensagem informando
o que foi enviado e para quem.
Depois atualizamos nosso :c:data:`last_offset` para podermos resetar a lista de updates.

Resetando updates
-----------------

Resetar a lista de updates é importante para que não recebamos novamente as mesmas atualizações,
dessa forma só respondemos uma única vez.
Para resetar, nós fazemos mais uma chamada à :c:func:`get_updates` e passamos o nosso :c:data:`last_offset`.
Dessa forma, na próxima chamada à :c:func:`get_updates` não iremos receber os mesmos Updates.

.. code-block:: c

   get_updates(echo, frame_update, last_offset, 100, 0, NULL);

Limpando estruturas
-------------------

No final nós liberamos a memória alocada com a função :c:func:`framebot_free`.

.. code-block:: c

   framebot_free(frame_update);

Aqui finalizamos nosso tutorial.

Código final disponível em `GitHub: Echo Bot`_.