#ifndef PAYMENTS_H
#define PAYMENTS_H


/* 
 * Currently support the currencies listed below 
 * https://core.telegram.org/bots/payments#supported-currencies
 */
#define CODE_AED  0   /* United Arab Emirates Dirham ...... AED 3.67        AED 36,726.99         */
#define CODE_AFN  1   /* Afghan Afghani ................... AFN70.94        AFN709,499.97         */
#define CODE_ALL  2   /* Albanian Lek ..................... 109,09ALL       1.090.999,98ALL       */
#define CODE_AMD  3   /* Armenian Dram .................... 482.48 AMD      4,824,800.11 AMD      */
#define CODE_ARS  4   /* Argentine Peso ................... ARS 24,83       ARS 248.349,99        */
#define CODE_AUD  5   /* Australian Dollar ................ AU$1.33         AU$13,334.03          */
#define CODE_AZN  6   /* Azerbaijani Manat ................ 1,69 AZN        16 995,00 AZN         */
#define CODE_BAM  7   /* Bosnia & Herzegovina Convertible . Mark   1,69     BAM    16.975,01 BAM  */
#define CODE_BDT  8   /* Bangladeshi Taka ................. BDT 83.98       BDT 839,899.98        */
#define CODE_BGN  9   /* Bulgarian Lev .................... 1,69 BGN        16 921,98 BGN         */
#define CODE_BND  10  /* Brunei Dollar .................... BND1,33         BND13.308,00          */
#define CODE_BOB  11  /* Bolivian Boliviano ............... BOB 6,85        BOB 68.501,18         */
#define CODE_BRL  12  /* Brazilian Real ................... R$ 3,72         R$ 37.254,02          */
#define CODE_CAD  13  /* Canadian Dollar .................. CA$1.30         CA$13,026.60          */
#define CODE_CHF  14  /* Swiss Franc ...................... 0.99 CHF        9'929.90 CHF          */
#define CODE_CLP  15  /* Chilean Peso ..................... CLP 629         CLP 6.292.199         */
#define CODE_CNY  16  /* Chinese Renminbi Yuan ............ CN¥6.42         CN¥64,258.98          */
#define CODE_COP  17  /* Colombian Peso ................... COP 2.902,89    COP 29.028.999,02     */
#define CODE_CRC  18  /* Costa Rican Colón ................ CRC563,40       CRC5.634.000,24       */
#define CODE_CZK  19  /* Czech Koruna ..................... 22,47 CZK       224 727,99 CZK        */
#define CODE_DKK  20  /* Danish Krone ..................... 6,44 DKK        64492,80 DKK          */
#define CODE_DOP  21  /* Dominican Peso ................... DOP49.49        DOP494,967.02         */
#define CODE_DZD  22  /* Algerian Dinar ................... DZD 116.92      DZD 1,169,299.40      */
#define CODE_EGP  23  /* Egyptian Pound ................... EGP 17.87       EGP 178,700.01        */
#define CODE_EUR  24  /* Euro ............................. 0,86 €          8 664,99 €            */
#define CODE_GBP  25  /* British Pound .................... £0.75           £7,544.50             */
#define CODE_GEL  26  /* Georgian Lari .................... 2,46 GEL        24 617,00 GEL         */
#define CODE_GTQ  27  /* Guatemalan Quetzal ............... GTQ7.33         GTQ73,360.27          */
#define CODE_HKD  28  /* Hong Kong Dollar ................. HK$7.84         HK$78,449.50          */
#define CODE_HNL  29  /* Honduran Lempira ................. HNL 23.83       HNL 238,329.54        */
#define CODE_HRK  30  /* Croatian Kuna .................... 6,40 HRK        64.000,98 HRK         */
#define CODE_HUF  31  /* Hungarian Forint ................. 277,99 HUF      2 779 998,67 HUF      */
#define CODE_IDR  32  /* Indonesian Rupiah ................ IDR13.991,00    IDR139.910.000,00     */
#define CODE_ILS  33  /* Israeli New Sheqel ............... ₪ 3.58          ₪ 35,885.03           */
#define CODE_INR  34  /* Indian Rupee ..................... ₹67.76          ₹677,624.97           */
#define CODE_ISK  35  /* Icelandic Króna .................. 106 ISK         1.063.000 ISK         */
#define CODE_JMD  36  /* Jamaican Dollar .................. JMD125.12       JMD1,251,200.03       */
#define CODE_JPY  37  /* Japanese Yen ..................... ¥108            ¥1,086,500            */
#define CODE_KES  38  /* Kenyan Shilling .................. KES101.09       KES1,010,999.98       */
#define CODE_KGS  39  /* Kyrgyzstani Som .................. 68-30 KGS       683 089-98 KGS        */
#define CODE_KRW  40  /* South Korean Won ................. ₩1,079          ₩10,799,000           */
#define CODE_KZT  41  /* Kazakhstani Tenge ................ KZT330-77       KZT3 307 799-99       */
#define CODE_LBP  42  /* Lebanese Pound ................... LBP 1,504.99    LBP 15,049,997.27     */
#define CODE_LKR  43  /* Sri Lankan Rupee ................. LKR 158.00      LKR 1,580,000.73      */
#define CODE_MAD  44  /* Moroccan Dirham .................. MAD 9.55        MAD 95,584.98         */
#define CODE_MDL  45  /* Moldovan Leu ..................... 16.86 MDL       168,620.13 MDL        */
#define CODE_MNT  46  /* Mongolian Tögrög ................. MNT2 401,00     MNT24 010 001,87      */
#define CODE_MUR  47  /* Mauritian Rupee .................. MUR34.40        MUR344,000.02         */
#define CODE_MVR  48  /* Maldivian Rufiyaa ................ 15.56 MVR       155,698.43 MVR        */
#define CODE_MXN  49  /* Mexican Peso ..................... MX$19.81        MX$198,111.99         */
#define CODE_MYR  50  /* Malaysian Ringgit ................ MYR3.99         MYR39,947.96          */
#define CODE_MZN  51  /* Mozambican Metical ............... MZN59.99        MZN599,995.27         */
#define CODE_NGN  52  /* Nigerian Naira ................... NGN356.00       NGN3,560,003.83       */
#define CODE_NIO  53  /* Nicaraguan Córdoba ............... NIO 31.11       NIO 311,100.01        */
#define CODE_NOK  54  /* Norwegian Krone .................. NOK 8,29        NOK 82 928,40         */
#define CODE_NPR  55  /* Nepalese Rupee ................... NPR108.47       NPR1,084,713.97       */
#define CODE_NZD  56  /* New Zealand Dollar ............... NZ$1.44         NZ$14,464.98          */
#define CODE_PAB  57  /* Panamanian Balboa ................ PAB 1.00        PAB 10,000.00         */
#define CODE_PEN  58  /* Peruvian Nuevo Sol ............... PEN 3.27        PEN 32,719.00         */
#define CODE_PHP  59  /* Philippine Peso .................. PHP52.67        PHP526,799.11         */
#define CODE_PKR  60  /* Pakistani Rupee .................. PKR115.62       PKR1,156,299.97       */
#define CODE_PLN  61  /* Polish Złoty ..................... 3,76 PLN        37 609,03 PLN         */
#define CODE_PYG  62  /* Paraguayan Guaraní ............... PYG 5.717       PYG 57.179.999        */
#define CODE_QAR  63  /* Qatari Riyal ..................... QAR 3.63        QAR 36,398.02         */
#define CODE_RON  64  /* Romanian Leu ..................... 4,02 RON        40.230,99 RON         */
#define CODE_RSD  65  /* Serbian Dinar .................... 100,49 RSD      1.004.954,99 RSD      */
#define CODE_RUB  66  /* Russian Ruble .................... 62,84 RUB       628 499,98 RUB        */
#define CODE_SAR  67  /* Saudi Riyal ...................... SAR 3.74        SAR 37,498.80         */
#define CODE_SEK  68  /* Swedish Krona .................... 8,96 SEK        89.662,50 SEK         */
#define CODE_SGD  69  /* Singapore Dollar ................. SGD1.34         SGD13,445.30          */
#define CODE_THB  70  /* Thai Baht ........................ ฿32.13          ฿321,360.01           */
#define CODE_TJS  71  /* Tajikistani Somoni ............... 8;99 TJS        89 990;99 TJS         */
#define CODE_TRY  72  /* Turkish Lira ..................... 4,54 TRY        45.466,01 TRY         */
#define CODE_TTD  73  /* Trinidad and Tobago Dollar ....... TTD6.64         TTD66,494.97          */
#define CODE_TWD  74  /* New Taiwan Dollar ................ NT$30.03        NT$300,380.03         */
#define CODE_TZS  75  /* Tanzanian Shilling ............... TZS2,275.00     TZS22,750,001.30      */
#define CODE_UAH  76  /* Ukrainian Hryvnia ................ 26,08UAH        260 899,47UAH         */
#define CODE_UGX  77  /* Ugandan Shilling ................. UGX3,757        UGX37,570,002         */
#define CODE_USD  78  /* United States Dollar ............. $1.00           $10,000.00            */
#define CODE_UYU  79  /* Uruguayan Peso ................... UYU 31,14       UYU 311.497,69        */
#define CODE_UZS  70  /* Uzbekistani Som .................. 7 964,99 UZS    79 649 997,29 UZS     */
#define CODE_VND  81  /* Vietnamese Đồng .................. 22.849 ₫        228.490.000 ₫         */
#define CODE_YER  82  /* Yemeni Rial ...................... YER 249.89      YER 2,498,999.94      */
#define CODE_ZAR  83  /* South African Rand ............... ZAR 12.66       ZAR 126,694.98        */


bool set_currency(uint32_t code);
int32_t get_currency();
int32_t set_provider_token(char *token);
void add_img_invoice(char *photo_url, uint64_t photo_size, uint32_t photo_width, uint32_t photo_heigth);
void remove_image_invoice();
void option_payment(bool n_name, bool n_phone, bool n_email, bool n_shipping_address, bool s_phone_to_provider,
bool s_email_to_provider, bool is_flexible);
Message *send_invoice(Bot *bot, int64_t chat_id, char * title, char *description, char *payload, char *start_parameter, char *prices,
     char *provider_data, int64_t reply_to_message_id, char *reply_markup);
bool answerPreCheckoutQuery(Bot *bot, char *pre_checkout_query_id, char *ok, char *error_message);


#endif
