Objetos
=======

Aqui você encontra os objetos implementados pela biblioteca.

Objetos exclusivos
------------------

Objetos que existem somente na biblioteca, e não possuem representação na API do Telegram.

.. c:type:: Bot
   
   Objeto que vai ser utilizado para referenciar seu bot nas funções da API.

   .. c:member:: char *token

      Seu `token` do Telegram.

   .. c:member:: User *user

      Objeto retornado da chamada à :c:func:`get_me`

Objetos da API
--------------

.. c:type:: User
   
   Veja `Telegram User`_

   .. _`Telegram User`: https://core.telegram.org/bots/api#user

   .. c:member:: long int id

   .. c:member:: bool is_bot

   .. c:member:: char *first_name

   .. c:member:: char *last_name

   .. c:member:: char *username

   .. c:member:: char *language_code

   .. c:member:: struct _user *next
