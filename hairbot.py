from h import *
import telebot

# data='''
# '''[1:-1]
# data=data.splitlines()
# data=[w for w in zip(data[::2],data[1::2])]
# data=[[w[0],w[1],w[0].split()[0]] for w in data]
# data=[[w[0],w[1].split(w[2]),w[2]] for w in data]
# data=[[w[0],[w[2]+e.strip() for e in w[1][1:]]] for w in data]
# data=[[e for e in [w[0]]+w[1]] for w in data]
# data=[[e.split(maxsplit=1)[1] for e in w] for w in data]
data=[
    ['What type of hair do you have?', 'Straight', 'Wavy', 'Curly', 'Frizz'],
    ['How long is your hair?', 'Short', 'Shoulder length', 'Long'],
    ['Is your hair dyed?', 'Yes', 'No', 'Bleached hair'],
    ['What kind of hair do you have?', 'Normal', 'Dry', 'Oily', 'Combined'],
    ['How long have you washed your hair?', 'Today', 'Yesterday', 'Two days ago', 'More than three days ago'],
    ['Are your hair ends split?', 'Yes', 'No'],
    ['Are your hair roots getting greasy fast?', 'Yes', 'No'],
    ['Do you have dull hair?', 'Yes', 'No'],
    ['Do you like your hair volume?', 'Yes', 'No'],
    ['What problems have you been facing lately?', 'Dandruff', 'Hair loss', 'Color loss', 'Hair without shine, split ends'],
    ['Choose the type of cosmetics?', 'Mass market', 'Professional care'],
]

def create_mes(res):
    mes=[]
    if res[10] == 1 and res[11] == 1:
        mes.append('''
            mass market
            shampoo: https://www.podrygka.ru/catalog/volosy/shampuni/213024-shampun-dlya-volos-garnier-fructis-protiv-perkhoti-2-v-1-ukreplyayushchiy-dlya-normalnykh-volos-250-/
            conditioner: https://goldapple.ru/101798-19000082103-collagen
            mask: https://www.letu.ru/product/akulya-sila-maska-dlya-volos-protiv-vypadeniya-i-perhoti-/119000146
            heat protection: https://rivegauche.ru/product/alan-hadash-heatbuffer-2-thermal-protective-hair-spray
            styling: https://www.letu.ru/product/kensuko-sredstvo-dlya-ukladki-i-vosstanovleniya-volos-kensuko-termozashchitnoe/93000447
        ''')
    if res[10] == 1 and res[11] == 2:
        mes.append('''
            prof
            shampoo: https://rivegauche.ru/product/loreal-professionnel-serie-expert-instant-clear-shampoo
            conditioner: https://goldapple.ru/catalog/product/view/id/185750/s/19000030319-flaky-itchy-scalp
            mask: https://www.letu.ru/product/spa-master-maska-piling-protiv-perhoti-i-vypadeniya-volos/117500255
            heat protection: https://rivegauche.ru/product/toni-guy-heat-protection-mist
            styling: https://goldapple.ru/19000039120-before-dry-lime
        ''')
    if res[10] == 1 and (res[3] == 1 or res[3] == 3) and res[11] == 1:
        mes.append('''
            Mass market
            shampoo: https://www.podrygka.ru/catalog/volosy/shampuni/213024-shampun-dlya-volos-garnier-fructis-protiv-perkhoti-2-v-1-ukreplyayushchiy-dlya-normalnykh-volos-250-/
            conditioner: https://goldapple.ru/19000084475-for-fair-hair
            mask: https://www.letu.ru/product/akulya-sila-maska-dlya-volos-protiv-vypadeniya-i-perhoti-/119000146
            heat protection: https://www.podrygka.ru/catalog/volosy/spetsia
            styling: https://goldapple.ru/30111100015-oblepihovyj
        ''')
    if res[10] == 1 and (res[3] == 1 or res[3] == 3) and res[11] == 2:
        mes.append('''
            shampoo: https://www.letu.ru/product/akulya-sila-maska-dlya-volos-protiv-vypadeniya-i-perhoti-/119000146
            conditioner: https://goldapple.ru/26873200001-blond-bar
            mask: https://rivegauche.ru/product/loreal-professionnel-serie-expert-blondifier-gloss-mask
            heat protection: https://www.letu.ru/product/estel-professional-sprei-termozashchita-dlya-okrashennyh-i-melirovannyh-volos-siyanie-tsveta-secrets/122200241
            styling: https://goldapple.ru/19000039120-before-dry-lime
        ''')
    if res[10] == 1 and res[4] == 3 and res[11] == 1:
        mes.append('''
            shampoo: https://www.podrygka.ru/catalog/volosy/shampuni/156253-shampun-dlya-volos-garnier-fructis-kokosovyy-balans-ukreplyayushchiy-dlya-volos-zhirnykh-u-korney-i-/
            conditioner: https://goldapple.ru/101798-19000082103-collagen
            mask: https://www.letu.ru/product/akulya-sila-maska-dlya-volos-protiv-vypadeniya-i-perhoti-/119000146
            heat protection: https://goldapple.ru/19000064232-verbena-vitamins
            styling: https://rivegauche.ru/product/schwarzkopf-henkel-taft-magiya-obyema-sukhoy-muss
        ''')
    if res[10] == 1 and res[4] == 3 and res[11] == 2:
        mes.append('''
            shampoo: https://rivegauche.ru/product/loreal-professionnel-serie-expert-instant-clear-shampoo
            conditioner: https://goldapple.ru/catalog/product/view/id/185750/s/19000030319-flaky-itchy-scalp
            mask: https://www.letu.ru/product/19lab-maska-dlya-zhirnogo-tipa-volos-legkost-i-obem-/115800836
            heat protection: https://goldapple.ru/1640400077-osis-flatliner
            styling: https://rivegauche.ru/product/sachajuan-volume-powder-200
        ''')
    if res[10] == 1 and res[1] == 4 and res[11] == 1:
        mes.append('''
            shampoo: https://goldapple.ru/19000107133-curls-waves
            conditioner: https://goldapple.ru/101798-19000082103-collagen
            mask: https://www.letu.ru/product/akulya-sila-maska-dlya-volos-protiv-vypadeniya-i-perhoti-/119000146
            heat protection: https://www.podrygka.ru/catalog/volosy/ukladka/219120-sprey-termozashchita-dlya-volos-levrana-natural-s-organicheskim-maslom-argany-150-ml/
            styling: https://www.letu.ru/product/kensuko-sredstvo-dlya-ukladki-i-vosstanovleniya-volos-kensuko-termozashchitnoe/93000447
        ''')
    if res[10] == 1 and res[1] == 4 and res[11] == 2:
        mes.append('''
            shampoo: https://rivegauche.ru/product/loreal-professionnel-serie-expert-instant-clear-shampoo
            conditioner: https://goldapple.ru/101161-19000058796-conditioner-active-curl
            mask: https://goldapple.ru/19000109705-smooth-curls-mask
            heat protection: https://rivegauche.ru/product/toni-guy-heat-protection-mist
            styling: https://goldapple.ru/19000031664-curls-transformer
        ''')
    if res[10] == 2 and res[11] == 1:
        mes.append('''
            shampoo: https://www.podrygka.ru/catalog/volosy/shampuni/219401-shampun-dlya-volos-belkosmex-oblepiha-organica-protiv-vypadeniya-400-g/
            conditioner: https://www.letu.ru/product/belkosmex-balzam-tonizirovanie-protiv-vypadeniya-volos/110000023
            mask: https://goldapple.ru/19000072279-red-pepper-pro-care
            heat protection: https://www.letu.ru/product/compliment-repeinyi-sprei-uhod-dlya-ukrepleniya-i-sily-volos-protiv-vypadeniya/105000547
            styling: https://goldapple.ru/1635800026-poroshok-mgnovennyj-ob-em
        ''')
    if res[10] == 2 and res[11] == 2:
        mes.append('''
            shampoo: https://rivegauche.ru/product/insight-loss-control-fortifying-shampoo
            conditioner: https://goldapple.ru/89310800004-dercos-aminexil
            mask: https://goldapple.ru/19000027311-care
            heat protection: https://www.letu.ru/product/essentiel-sprei-stimuliruyushchii-protiv-vypadeniya-volos-keratin-force/45500025
            styling: https://goldapple.ru/19000061138-styling-powder
        ''')
    if res[10] == 2 and (res[3] == 1 or res[3] == 3) and res[11] == 1:
        mes.append('''
            shampoo: https://www.podrygka.ru/catalog/volosy/shampuni/219401-shampun-dlya-volos-belkosmex-oblepiha-organica-protiv-vypadeniya-400-g/
            conditioner: https://goldapple.ru/19000084475-for-fair-hair
            mask: https://goldapple.ru/19000072279-red-pepper-pro-care
            heat protection: https://www.podrygka.ru/catalog/volosy/spetsialnye_sredstva/135717-ekspress-konditsioner-dlya-volos-loreal-elseve-ekspert-tsveta-dvoynoy-eliksir-dlya-okrashennykh-i-me/
            styling: https://goldapple.ru/1635800026-poroshok-mgnovennyj-ob-em
        ''')
    if res[10] == 2 and (res[3] == 1 or res[3] == 3) and res[11] == 2:
        mes.append('''
            shampoo: https://rivegauche.ru/product/insight-loss-control-fortifying-shampoo
            conditioner: https://goldapple.ru/26873200001-blond-bar
            mask: https://goldapple.ru/19000027311-care
            heat protection: https://www.letu.ru/product/essentiel-sprei-stimuliruyushchii-protiv-vypadeniya-volos-keratin-force/45500025
            styling: https://rivegauche.ru/product/philip-kingsley-pure-colour-frizz-fighting-gloss
        ''')
    if res[10] == 2 and res[4] == 3 and res[11] == 1:
        mes.append('''
            shampoo: https://www.podrygka.ru/catalog/volosy/shampuni/156253-shampun-dlya-volos-garnier-fructis-kokosovyy-balans-ukreplyayushchiy-dlya-volos-zhirnykh-u-korney-i-/
            conditioner: https://www.letu.ru/product/belkosmex-balzam-tonizirovanie-protiv-vypadeniya-volos/110000023
            mask: https://www.letu.ru/product/cafe-mimi-maska-3-gliny-dlya-volos-zhirnyh-u-kornei-i-suhih-na-konchikah-220-ml/105000265
            heat protection: https://www.letu.ru/product/compliment-repeinyi-sprei-uhod-dlya-ukrepleniya-i-sily-volos-protiv-vypadeniya/105000547
            styling: https://rivegauche.ru/product/schwarzkopf-henkel-taft-magiya-obyema-sukhoy-muss
        ''')
    if res[10] == 2 and res[4] == 3 and res[11] == 2:
        mes.append('''
            shampoo: https://goldapple.ru/19000003235-sebum-control-shampoo
            conditioner: https://www.letu.ru/product/19lab-konditsioner-dlya-zhirnogo-tipa-volos-legkost-i-obem-/115800835
            mask: https://goldapple.ru/19000027311-care
            heat protection: https://goldapple.ru/1640400077-osis-flatliner
            styling: https://goldapple.ru/19000061138-styling-powder
        ''')
    if res[10] == 2 and res[1] == 4 and res[11] == 1:
        mes.append('''
            shampoo: https://www.podrygka.ru/catalog/volosy/shampuni/219401-shampun-dlya-volos-belkosmex-oblepiha-organica-protiv-vypadeniya-400-g/
            conditioner: https://rivegauche.ru/product/beautific-curl-me-on-hydrating-conditioner
            mask: https://goldapple.ru/19000072279-red-pepper-pro-care
            heat protection: https://www.podrygka.ru/catalog/volosy/ukladka/219120-sprey-termozashchita-dlya-volos-levrana-natural-s-organicheskim-maslom-argany-150-ml/
            styling: https://www.podrygka.ru/catalog/volosy/ukladka/222629-muss-dlya-volos-hair-pro-concept-dlya-ukladki-kudryashek-150-ml/
        ''')
    if res[10] == 2 and res[1] == 4 and res[11] == 2:
        mes.append('''
            shampoo: https://rivegauche.ru/product/insight-loss-control-fortifying-shampoo
            conditioner: https://goldapple.ru/101161-19000058796-conditioner-active-curl
            mask: https://goldapple.ru/19000109705-smooth-curls-mask
            heat protection: https://rivegauche.ru/product/epica-professional-silk-waves-spray-curly-hair
            styling: https://goldapple.ru/19000061138-styling-powder
        ''')
    if res[10] == 3 and res[11] == 1:
        mes.append('''
            shampoo: https://rivegauche.ru/product/matrix-total-results-keep-vivid-shampoo
            conditioner: https://goldapple.ru/19760324157-be-color-arkost-i-zasita-cveta
            mask: https://www.letu.ru/product/dolce-milk-maska-dlya-okrashennyh-volos-miss-klubnichnyi-kompromiss-/88500008
            heat protection: https://www.letu.ru/product/eden-sprei-konditsioner-dlya-volos-termozashchita/100600258
            styling: https://goldapple.ru/19000119831-for-hair-styling-super-fixation
        ''')
    if res[10] == 3 and res[11] == 2:
        mes.append('''
            shampoo: https://rivegauche.ru/product/joico-k-pak-color-therapy-color-protecting-shampoo
            conditioner: https://goldapple.ru/19760327046-angel-rinse
            mask: https://rivegauche.ru/product/mone-professional-lucky-leopard-reconstructive-therapy-mask
            heat protection: https://goldapple.ru/24100100035-vitamino-color
            styling: https://www.letu.ru/product/philip-kingsley-sprei-blesk-dlya-ukladki-okrashennyh-volos/117201624
        ''')
    if res[10] == 3 and (res[3] == 1 or res[3] == 3) and res[11] == 1:
        mes.append('''
            shampoo: https://www.podrygka.ru/catalog/volosy/shampuni/213098-shampun-dlya-volos-syoss-blonde-s-pigmentom-dlya-osvetlennykh-i-melirovannykh-volos-450-ml/
            conditioner: https://goldapple.ru/19000084475-for-fair-hair
            mask: https://rivegauche.ru/product/loreal-paris-elseve-ekspert-tsveta-fioletovaya-maska
            heat protection: https://www.podrygka.ru/catalog/volosy/spetsialnye_sredstva/135717-ekspress-konditsioner-dlya-volos-loreal-elseve-ekspert-tsveta-dvoynoy-eliksir-dlya-okrashennykh-i-me/
            styling: https://goldapple.ru/30111100015-oblepihovyj
        ''')
    if res[10] == 3 and (res[3] == 1 or res[3] == 3) and res[11] == 2:
        mes.append('''
            shampoo: https://goldapple.ru/19000094173-lilu-bubbles-color-lemonade-shampoo
            conditioner: https://goldapple.ru/26873200001-blond-bar
            mask: https://rivegauche.ru/product/loreal-professionnel-serie-expert-blondifier-gloss-mask
            heat protection: https://www.letu.ru/product/estel-professional-sprei-termozashchita-dlya-okrashennyh-i-melirovannyh-volos-siyanie-tsveta-secrets/122200241
            styling: https://rivegauche.ru/product/philip-kingsley-pure-colour-frizz-fighting-gloss
        ''')
    if res[10] == 3 and res[4] == 3 and res[11] == 1:
        mes.append('''
            shampoo: https://rivegauche.ru/product/matrix-total-results-keep-vivid-shampoo
            conditioner: https://goldapple.ru/19760324157-be-color-arkost-i-zasita-cveta
            mask: https://www.letu.ru/product/dolce-milk-maska-dlya-okrashennyh-volos-miss-klubnichnyi-kompromiss-/88500008
            heat protection: https://goldapple.ru/19000064232-verbena-vitamins
            styling: https://rivegauche.ru/product/schwarzkopf-henkel-taft-magiya-obyema-sukhoy-muss
        ''')
    if res[10] == 3 and res[4] == 3 and res[11] == 2:
        mes.append('''
            shampoo: https://goldapple.ru/19000003235-sebum-control-shampoo
            conditioner: https://goldapple.ru/26873200001-blond-bar
            mask: https://rivegauche.ru/product/mone-professional-lucky-leopard-reconstructive-therapy-mask
            heat protection: https://www.letu.ru/product/eden-sprei-konditsioner-dlya-volos-termozashchita/100600258
            styling: https://rivegauche.ru/product/sachajuan-volume-powder-200
        ''')
    if res[10] == 3 and res[1] == 4 and res[11] == 1:
        mes.append('''
            shampoo: https://goldapple.ru/19000107133-curls-waves
            conditioner: https://goldapple.ru/19000084475-for-fair-hair
            mask: https://goldapple.ru/19000107135-curls-waves
            heat protection: https://www.podrygka.ru/catalog/volosy/spetsialnye_sredstva/135717-ekspress-konditsioner-dlya-volos-loreal-elseve-ekspert-tsveta-dvoynoy-eliksir-dlya-okrashennykh-i-me/
            styling: https://www.podrygka.ru/catalog/volosy/ukladka/222629-muss-dlya-volos-hair-pro-concept-dlya-ukladki-kudryashek-150-ml/
        ''')
    if res[10] == 3 and res[1] == 4 and res[11] == 2:
        mes.append('''
            shampoo: https://goldapple.ru/19000094173-lilu-bubbles-color-lemonade-shampoo
            conditioner: https://goldapple.ru/101161-19000058796-conditioner-active-curl
            mask: https://goldapple.ru/19000045215-frizz-free
            heat protection: https://rivegauche.ru/product/epica-professional-silk-waves-spray-curly-hair
            styling: https://goldapple.ru/19000031664-curls-transformer
        ''')
    if res[10] == 4 and res[11] == 1:
        mes.append('''
            shampoo: https://www.podrygka.ru/catalog/volosy/shampuni/206410-shampun-dlya-volos-marusya-s-ekstraktom-mango-dlya-normalnykh-volos-400-ml/
            conditioner: https://www.letu.ru/product/elseve-legkii-smyagchayushchii-balzam-uhod-elseve-roskosh-kokosovogo-masla-dlya-normalnyh-i-sklonnyh-k-suhosti-volos/104300013
            mask: https://podrygka.ru/catalog/volosy/maski_dlya_volos/205735-maska-dlya-volos-loreal-elseve-roskosh-kokosovogo-masla-5-v-1-dlya-normalnykh-i-sklonnykh-k-sukhosti/
            heat protection: https://www.podrygka.ru/catalog/volosy/ukladka/219120-sprey-termozashchita-dlya-volos-levrana-natural-s-organicheskim-maslom-argany-150-ml/
            styling: https://goldapple.ru/28222300001-volume-up-shine
        ''')
    if res[10] == 4 and res[11] == 2:
        mes.append('''
            shampoo: https://goldapple.ru/catalog/product/view/id/172929/s/19000018059-fibre-clinix-hydrate
            conditioner: https://www.letu.ru/product/coiffance-pitatelnyi-konditsioner-dlya-normalnyh-i-suhih-volos-nutri/123100053
            mask: https://goldapple.ru/19760311147-dry-hair-nourishing-mask
            heat protection: https://goldapple.ru/19000038810-heat-protection-hair-spray
            styling: https://www.letu.ru/product/evo-mr.fantastik-universalnyi-stailing-sprei-mister-fantastic-blowout-spray/113600014
        ''')
    if res[10] == 4 and res[4] == 2 and res[11] == 1:
        mes.append('''
            shampoo: https://rivegauche.ru/product/garnier-fructis-sos-vosstanovlenie-dlya-sekuschikhsya-i-povrezhdennykh-volos-4
            conditioner: https://goldapple.ru/19000072292-keratin-pro-care
            mask: https://www.letu.ru/product/bisou-maska-siyanie-dlya-suhih-i-tusklyh-volos-ultrauvlazhnenie/105500247
            heat protection: https://rivegauche.ru/product/concept-fusion-ultra-moist-spray
            styling: https://rivegauche.ru/product/taft-ultimate-pena-dlya-ukladki
        ''')
    if res[10] == 4 and res[4] == 2 and res[11] == 2:
        mes.append('''
            shampoo: https://rivegauche.ru/product/mone-professional-volume-flex-shampoo
            conditioner: https://goldapple.ru/19000091623-basilico-mandorla
            mask: https://rivegauche.ru/product/wella-professionals-invigo-volume-boost-crystal-mask
            heat protection: https://rivegauche.ru/product/loreal-professionnel-serie-expert-pro-longer-heat-protecting-cream
            styling: https://goldapple.ru/19000105683-gold-protein-styling-cream-dull
        ''')
    if res[4] == 1:
        mes.append('''
            recommendations for normal hair
            «Use a mild shampoo for normal hair, not overloaded with nutrients, 2 times a week. Also, do not forget about balms and conditioners, which should be applied only to the length of the hair;
            after each shampooing, use moisturizers to prevent overdrying of the hair (especially if you wash your hair often);
            do not wash your hair with too hot water, rinse the shampoo well, otherwise its residue can make the hair sticky and dull;
            comb your hair before washing your hair - this way they will be washed better and combed well;
            if you do not need to constantly do styling, let your hair dry without a hair dryer.»
        ''')
    if res[4] == 2:
        mes.append('''
            recommendations for dry hair
            «Wash your hair 1-2 times a week using shampoo for dry or damaged hair;
            Use oils, moisturizing sprays and serums to prevent breakage and tangles. Once a week, be sure to use nourishing masks;
            Choose the right combs - best with natural bristles or wooden teeth. Metal combs are best avoided;
            Use a hair dryer, iron and curling iron as little as possible. And if you take them in your hands, then be sure to use them together with thermal protective agents. Dry your hair with a hairdryer in the direction from the roots to the tips;
            Regularly do a head massage - it improves blood circulation and does not allow the hair to dry out.»
        ''')
    if res[4] == 3:
        mes.append('''
            recommendations for oily hair
            «Ideal shampoo labeled "for daily use" or one that helps regulate sebum production;
            Avoid products with silicones and oils in the composition - these ingredients will quickly "steal" the freshness from your hair;
            Lather your head at least twice, gently massaging your hair. It is ideal to leave the shampoo on the hair for a couple of minutes so that the fat is completely dissolved. Rinse with warm water, thoroughly washing the roots and length;»
        ''')
    if res[4] == 4:
        mes.append('''
            recommendations for combined hair
            «Wash your hair as needed. Buy shampoo for normal or mixed type hair;
            apply conditioner, masks and other care products only to the ends of the hair (or distribute along the entire length if the product is not too heavy);
            try applying kefir or yogurt to the hair roots half an hour before washing, and olive or coconut oil to the tips. This should help deal with oiliness at the roots and dryness at the ends;
            dry your hair at low temperatures, do not abuse the curling iron and be sure to use heat protectants on the tips.»
        ''')
    if  (res[3] == 1 or res[3] == 3):
        mes.append('''
            Recommendations for dyed hair
            «The more often you wash your hair, the faster the dye is washed out and the color fades. Frequent washing also strips hair of its natural oils, making it appear dry, dull, and lifeless. Therefore, experts advise washing your hair no more than two or three times a week, if there is no need or individual need to do this more often.
            Be sure to pause between coloring sessions, at least 4 to 5 weeks.
            Heat protectants are essential for any type of hair, especially colored hair. Use a heat protectant before styling to minimize exposure to hot air or tools.»
        ''')
    return mes


def strip_lines(s):
    return '\n'.join([w.strip() for w in s.splitlines() if w.strip()])

try:
    db=json.loads(open('hairbot.json').read())
except:
    db={}

def save_db():
    open('hairbot.json','w').write(json.dumps(db))

def save_to_db(*a):
    ks=a[:-2]
    d=db
    for w in ks:
        if w not in d:
            d[w]={}
        d=d[w]
    d[a[-2]]=a[-1]
    save_db()

def db_set_if_not_present(*a):
    ks=a[:-2]
    d=db
    for w in ks:
        if w not in d:
            d[w]={}
        d=d[w]
    if a[-2] not in d:
        d[a[-2]]=a[-1]
    save_db()

def send_q(message,index):
    _markup=telebot.types.ReplyKeyboardMarkup(resize_keyboard=True)
    for q,w in enumerate(data[index][1:]):
        _markup.add(telebot.types.KeyboardButton(f'{index+1}.{q+1} {w}'))
    bot.send_message(message.chat.id, f'{index+1} {data[index][0]}',reply_markup=_markup)

def get_id(message):
    return message.from_user.username


def test(l,r):
    ll=len(l)
    if ll!=len(data):
        for w in range(1,len(data[ll])):
            l[ll+1]=w
            test(l,r)
        del l[ll+1]
    else:
        r.append(bytes(l.values()))

# r=[]
# test({},r)

# f=set()
# for w in r:
#     for e in create_mes({q+1:e for q,e in enumerate(w)}):
#         f.add(e)
# f={w:set() for w in f}
# for w in r:
#     for e in create_mes({q+1:e for q,e in enumerate(w)}):
#         f[e].add(w)
# for q in f:
#     for w in f:
#         if f[q]-f[w] and f[w]-f[q]:
#             print(f[q],f[w])

# ss=[]
# for w in r:
#     ss.append(f'''std::cout << "    {tuple(w)}: " << f<(__int128_t({int.from_bytes(w[8:],'little')})<<64)+{int.from_bytes(w[:8],'little')}>() << ",\\n";''')
# modules.random.shuffle(ss)
# for w in ss:
#     print(w)


# exit()
##########################################################################

bot = telebot.TeleBot('5808756779:AAFTALOqeIapEnvXz9Ek4_d3-Nx7rRZnviw')

@bot.message_handler(commands=["start"])
def start(message):
    try:
        save_to_db(get_id(message),{})
        markup=telebot.types.ReplyKeyboardRemove()
        # markup=telebot.types.ForceReply()
        bot.send_message(
            message.chat.id,
            strip_lines('''
                Hi, this is a bot that will help you find your perfect hair products!
                First, take 2 photos as an example,
                send them two messages (one per message) and
                take a small test!
            '''),
            reply_markup=markup)
        bot.send_photo(message.chat.id, open('hairbot1.jpg', 'rb'))
        bot.send_photo(message.chat.id, open('hairbot2.jpg', 'rb'))
    except Exception:
        print(modules.traceback.format_exc())
        pass


lock=modules.threading.Lock()
@bot.message_handler(content_types=['photo','document'])
def doc(message):
    try:
        with lock:
            markup=telebot.types.ReplyKeyboardRemove()
            # markup=telebot.types.ForceReply()
            db_set_if_not_present(get_id(message),'photos',0)
            save_to_db(get_id(message),'photos',db[get_id(message)]['photos']+1)
            if db[get_id(message)]['photos']==1:
                bot.send_message(message.chat.id, f'Nice! One photo was received! now the second one has come!',reply_markup=markup)
            else:
                bot.send_message(message.chat.id, f'Great! all photos were received!',reply_markup=markup)
                send_q(message,0)
    except Exception:
        print(modules.traceback.format_exc())
        pass


@bot.message_handler(content_types=["text"])
def handle_text(message):
    try:
        t=message.text
        if t.split():
            num=t.split(maxsplit=1)[0].split('.')
            if len(num)==2 and all([w.isdecimal() for w in num]):
                num=[int(w)-1 for w in num]
                if num[0] in range(len(data)):
                    save_to_db(get_id(message),'test',num[0]+1,num[1]+1)
                    if num[0]+1 in range(len(data)):
                        send_q(message,num[0]+1)
                    else:
                        markup=telebot.types.ReplyKeyboardRemove()
                        db_set_if_not_present(get_id(message),'test',{})
                        res=db[get_id(message)]['test']
                        if all([w+1 in res and res[w+1]-1 in range(len(data[w])) for w in range(len(data))]):
                            mes=create_mes(res)
                            mes='\n\n'.join([strip_lines(w) for w in mes])
                            bot.send_message(message.chat.id, f'''{mes}''',reply_markup=markup)
                        else:
                            start(message)
                return
        start(message)
    except Exception:
        print(modules.traceback.format_exc())
        pass

bot.polling(none_stop=True, interval=0)
print()
save_db()




