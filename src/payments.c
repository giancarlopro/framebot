#include <framebot/framebot.h>

/* option boolean to invoice */
struct _option_invoice {
    char *n_name;
    char *n_phone;
    char *n_email;
    char *n_shipping_address;
    char *s_phone_to_provider;
    char *s_email_to_provider;
    char *is_flexible;
};

/* image to show on invoice */
struct _img_invoice {
    char *photo_url;
    uint64_t photo_size;
    int32_t photo_width;
    uint32_t photo_heigth;
};

/*  */
struct _s_invoice {
    char *ptoken;
    uint32_t currency_code;
    struct _option_invoice option;
    struct _img_invoice img;
};

struct _s_invoice s_invoice = {
    .ptoken = NULL,
    .currency_code = CODE_USD,
    .option = {
        .n_name = "false",
        .n_phone = "false",
        .n_email = "false",
        .n_shipping_address = "false",
        .s_phone_to_provider = "false",
        .s_email_to_provider = "false",
        .is_flexible = "false"
    },
    .img = {
        .photo_url = NULL,
        .photo_size = 0,
        .photo_width = 0,
        .photo_heigth = 0
    }
};

#define SIZECURRENCY 84

/* https://core.telegram.org/bots/payments#supported-currencies */
static char *currency[SIZECURRENCY] =
{
"AED", /* United Arab Emirates Dirham ......... AED 3.67       AED 36,726.99     */
"AFN", /* Afghan Afghani ...................... AFN70.94       AFN709,499.97     */
"ALL", /* Albanian Lek ........................ 109,09ALL      1.090.999,98ALL   */
"AMD", /* Armenian Dram ....................... 482.48 AMD     4,824,800.11 AMD  */
"ARS", /* Argentine Peso ...................... ARS 24,83      ARS 248.349,99    */
"AUD", /* Australian Dollar ................... AU$1.33        AU$13,334.03      */
"AZN", /* Azerbaijani Manat ................... 1,69 AZN       16 995,00 AZN     */
"BAM", /* Bosnia & Herzegovina Convertible Mark 1,69 BAM  16.975,01 BAM     */
"BDT", /* Bangladeshi Taka .................... BDT 83.98      BDT 839,899.98    */
"BGN", /* Bulgarian Lev ....................... 1,69 BGN       16 921,98 BGN     */
"BND", /* Brunei Dollar ....................... BND1,33        BND13.308,00      */
"BOB", /* Bolivian Boliviano .................. BOB 6,85       BOB 68.501,18     */
"BRL", /* Brazilian Real ...................... R$ 3,72        R$ 37.254,02      */
"CAD", /* Canadian Dollar ..................... CA$1.30        CA$13,026.60      */
"CHF", /* Swiss Franc ......................... 0.99 CHF       9'929.90 CHF      */
"CLP", /* Chilean Peso ........................ CLP 629        CLP 6.292.199     */
"CNY", /* Chinese Renminbi Yuan ............... CN¥6.42        CN¥64,258.98      */
"COP", /* Colombian Peso ...................... COP 2.902,89    COP 29.028.999,02*/
"CRC", /* Costa Rican Colón ................... CRC563,40      CRC5.634.000,24   */
"CZK", /* Czech Koruna ........................ 22,47 CZK      224 727,99 CZK    */
"DKK", /* Danish Krone ........................ 6,44 DKK       64492,80 DKK      */
"DOP", /* Dominican Peso ...................... DOP49.49       DOP494,967.02     */
"DZD", /* Algerian Dinar ...................... DZD 116.92     DZD 1,169,299.40  */
"EGP", /* Egyptian Pound ...................... EGP 17.87      EGP 178,700.01    */
"EUR", /* Euro ................................ 0,86 €         8 664,99 €        */
"GBP", /* British Pound ....................... £0.75          £7,544.50         */
"GEL", /* Georgian Lari ....................... 2,46 GEL       24 617,00 GEL     */
"GTQ", /* Guatemalan Quetzal .................. GTQ7.33        GTQ73,360.27      */
"HKD", /* Hong Kong Dollar .................... HK$7.84        HK$78,449.50      */
"HNL", /* Honduran Lempira .................... HNL 23.83      HNL 238,329.54    */
"HRK", /* Croatian Kuna ....................... 6,40 HRK       64.000,98 HRK     */
"HUF", /* Hungarian Forint .................... 277,99 HUF     2 779 998,67 HUF  */
"IDR", /* Indonesian Rupiah ................... IDR13.991,00   IDR139.910.000,00 */
"ILS", /* Israeli New Sheqel .................. ₪ 3.58         ₪ 35,885.03       */
"INR", /* Indian Rupee ........................ ₹67.76         ₹677,624.97       */
"ISK", /* Icelandic Króna ..................... 106 ISK        1.063.000 ISK     */
"JMD", /* Jamaican Dollar ..................... JMD125.12      JMD1,251,200.03   */
"JPY", /* Japanese Yen ........................ Yen ¥108       ¥1,086,500        */
"KES", /* Kenyan Shilling ..................... KES101.09      KES1,010,999.98   */
"KGS", /* Kyrgyzstani Som ..................... 68-30 KGS      683 089-98 KGS    */
"KRW", /* South Korean Won .................... ₩1,079         ₩10,799,000       */
"KZT", /* Kazakhstani Tenge ................... KZT330-77      KZT3 307 799-99   */
"LBP", /* Lebanese Pound ...................... LBP 1,504.99   LBP 15,049,997.27 */
"LKR", /* Sri Lankan Rupee .................... LKR 158.00     LKR 1,580,000.73  */
"MAD", /* Moroccan Dirham ..................... MAD 9.55       MAD 95,584.98     */
"MDL", /* Moldovan Leu ........................ 16.86 MDL      168,620.13 MDL    */
"MNT", /* Mongolian Tögrög .................... MNT2 401,00    MNT24 010 001,87  */
"MUR", /* Mauritian Rupee ..................... MUR34.40       MUR344,000.02     */
"MVR", /* Maldivian Rufiyaa ................... 15.56 MVR      155,698.43 MVR    */
"MXN", /* Mexican Peso ........................ MX$19.81       MX$198,111.99     */
"MYR", /* Malaysian Ringgit ................... MYR3.99        MYR39,947.96      */
"MZN", /* Mozambican Metical .................. MZN59.99       MZN599,995.27     */
"NGN", /* Nigerian Naira ...................... NGN356.00      NGN3,560,003.83   */
"NIO", /* Nicaraguan Córdoba .................. NIO 31.11      NIO 311,100.01    */
"NOK", /* Norwegian Krone ..................... NOK 8,29       NOK 82 928,40     */
"NPR", /* Nepalese Rupee ...................... NPR108.47      NPR1,084,713.97   */
"NZD", /* New Zealand Dollar .................. NZ$1.44        NZ$14,464.98      */
"PAB", /* Panamanian Balboa ................... PAB 1.00       PAB 10,000.00     */
"PEN", /* Peruvian Nuevo Sol .................. PEN 3.27       PEN 32,719.00     */
"PHP", /* Philippine Peso ..................... PHP52.67       PHP526,799.11     */
"PKR", /* Pakistani Rupee ..................... PKR115.62      PKR1,156,299.97   */
"PLN", /* Polish Złoty ........................ 3,76 PLN       37 609,03 PLN     */
"PYG", /* Paraguayan Guaraní .................. PYG 5.717      PYG 57.179.999    */
"QAR", /* Qatari Riyal ........................ QAR 3.63       QAR 36,398.02     */
"RON", /* Romanian Leu ........................ 4,02 RON       40.230,99 RON     */
"RSD", /* Serbian Dinar ....................... 100,49 RSD     1.004.954,99 RSD  */
"RUB", /* Russian Ruble ....................... 62,84 RUB      628 499,98 RUB    */
"SAR", /* Saudi Riyal ......................... SAR 3.74       SAR 37,498.80     */
"SEK", /* Swedish Krona ....................... 8,96 SEK       89.662,50 SEK     */
"SGD", /* Singapore Dollar .................... SGD1.34        SGD13,445.30      */
"THB", /* Thai Baht ........................... ฿32.13         ฿321,360.01       */
"TJS", /* Tajikistani Somoni .................. 8;99 TJS       89 990;99 TJS     */
"TRY", /* Turkish Lira ........................ 4,54 TRY       45.466,01 TRY     */
"TTD", /* Trinidad and Tobago Dollar .......... TTD6.64        TTD66,494.97      */
"TWD", /* New Taiwan Dollar ................... NT$30.03       NT$300,380.03     */
"TZS", /* Tanzanian Shilling .................. TZS2,275.00    TZS22,750,001.30  */
"UAH", /* Ukrainian Hryvnia ................... 26,08UAH       260 899,47UAH     */
"UGX", /* Ugandan Shilling .................... UGX3,757       UGX37,570,002     */
"USD", /* United States Dollar ................ $1.00          $10,000.00        */
"UYU", /* Uruguayan Peso ...................... UYU 31,14      UYU 311.497,69    */
"UZS", /* Uzbekistani Som ..................... 7 964,99 UZS   79 649 997,29 UZS */
"VND", /* Vietnamese Đồng ..................... 22.849 ₫       228.490.000 ₫     */
"YER", /* Yemeni Rial ......................... YER 249.89     YER 2,498,999.94  */
"ZAR"  /* South African Rand .................. ZAR 12.66      ZAR 126,694.98    */
};


/*
 * ( currency ) https://core.telegram.org/bots/api#sendinvoice 
 */

bool set_currency(uint32_t code){
    if(code >= SIZECURRENCY)
        return false;

    s_invoice.currency_code = code;

    return true;
}


int32_t get_currency(){
    return s_invoice.currency_code;
}

/*
 * ( provider_token ) https://core.telegram.org/bots/api#sendinvoice 
 */
int32_t set_provider_token(char *token){
    if(token == 0)
        return false;

    if(s_invoice.ptoken != NULL)
        ffree(s_invoice.ptoken);

    s_invoice.ptoken = alloc_string(token);

    return true;
}


/*
 * ( photo_url photo_size photo_width photo_height ) https://core.telegram.org/bots/api#sendinvoice
 */
void add_img_invoice(char *photo_url, uint64_t photo_size, uint32_t photo_width, uint32_t photo_heigth){
    struct _img_invoice *i;

    if(photo_url == NULL){
        return;
    }

    i = &s_invoice.img;

    if(i->photo_url != NULL){
        remove_image_invoice();
    }

    i->photo_url = alloc_string(photo_url);
    i->photo_size = photo_size;
    i->photo_width = photo_width;
    i->photo_heigth = photo_heigth;
}

void remove_image_invoice(){
    struct _img_invoice *i;
    i = &s_invoice.img;

    if(i->photo_url != NULL)
        ffree(i->photo_url);

    i->photo_url = NULL;
    i->photo_size = 0;
    i->photo_width = 0;
    i->photo_heigth = 0;
}


/*
 * ( need_name need_phone_number need_email need_shipping_address send_phone_number_to_provider send_email_to_provider is_flexible )
 * https://core.telegram.org/bots/api#sendinvoice
 */
void option_payment(bool n_name, bool n_phone, bool n_email, bool n_shipping_address, bool s_phone_to_provider,
    bool s_email_to_provider, bool is_flexible){
    struct _option_invoice *op;

    op = &s_invoice.option;

    op->n_name = n_name > 0 ? "true" : "false";
    op->n_phone = n_phone > 0 ? "true" : "false";
    op->n_email = n_email > 0 ? "true" : "false";
    op->n_shipping_address = n_shipping_address > 0 ? "true" : "false";
    op->s_phone_to_provider = s_phone_to_provider > 0 ? "true" : "false";
    op->s_email_to_provider = s_email_to_provider > 0 ? "true" : "false";
    op->is_flexible = is_flexible > 0 ? "true" : "false";

}

/*
 * https://core.telegram.org/bots/api#sendinvoice
 */
Message *send_invoice(Bot *bot, int64_t chat_id, char * title, char *description, char *payload, char *start_parameter, char *prices,
     char *provider_data, int64_t reply_to_message_id, char *reply_markup){

    Message *message;
    refjson *s_json;

    s_json = generic_method_call(bot->token, API_sendInvoice,
        chat_id, title, description, payload, s_invoice.ptoken, start_parameter, currency[s_invoice.currency_code], prices,
        CONVERT_URL_STRING(provider_data), CONVERT_URL_STRING(s_invoice.img.photo_url), s_invoice.img.photo_size, s_invoice.img.photo_width,
        s_invoice.img.photo_heigth, s_invoice.option.n_name, s_invoice.option.n_phone, s_invoice.option.n_email, s_invoice.option.n_shipping_address,
        s_invoice.option.s_phone_to_provider, s_invoice.option.s_email_to_provider, s_invoice.option.is_flexible,
        CONVERT_URL_BOOLEAN(get_notification()), reply_to_message_id, CONVERT_URL_STRING(reply_markup));

    if(!s_json)
        return NULL;

    message = message_parse(s_json->content);

    close_json ( s_json );

    return message;
}


/*
 * https://core.telegram.org/bots/api#answershippingquery
 */
bool answerShippingQuery(Bot *bot, char *shipping_query_id, bool ok, char *shipping_options, char *error_message){

    bool result;
    refjson *s_json;

    s_json = generic_method_call(bot->token, API_answerShippingQuery,
        shipping_query_id, CONVERT_URL_BOOLEAN(ok), CONVERT_URL_STRING(shipping_options),
        CONVERT_URL_STRING(error_message));

    if(!s_json)
        return -1;

    result = json_is_true(s_json->content);

    close_json(s_json);

    return result;
}


/*
 * https://core.telegram.org/bots/api#answerprecheckoutquery
 *
 */
bool answerPreCheckoutQuery(Bot *bot, char *pre_checkout_query_id, bool ok, char *error_message){

    bool result;
    refjson *s_json;

    s_json = generic_method_call(bot->token, API_answerPreCheckoutQuery,
        pre_checkout_query_id, CONVERT_URL_BOOLEAN(ok), CONVERT_URL_STRING(error_message));

    if(!s_json)
        return -1;

    result = json_is_true(s_json->content);

    close_json(s_json);

    return result;
}
