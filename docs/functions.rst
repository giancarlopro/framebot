Funções
=======

Aqui você encontra as funções implementadas pela biblioteca.

Funções exclusivas
------------------

Funções que são implementadas pela biblioteca, mas não pela API do Telegram.

.. c:function:: void framebot_init ()

   Essa função é utilizada para iniciar a biblioteca e suas dependencias.

.. c:function:: Bot *framebot (const char *token)

   Essa função é chamada para inicializar um objeto do tipo :c:type:`Bot`, 
   que será usado sempre que for preciso utilizar uma função da API do Telegram.

.. _api-func:

Funções da API
--------------

.. c:function:: User *get_me (const char *token)

   Veja em `Telegram API`_

   .. _`Telegram API`: https://core.telegram.org/bots/api#getme

   Uma função para testar seu `token`.
   Requer o parâmetro `token`, e retorna as informações básicas do seu bot em um objeto :c:type:`User`.