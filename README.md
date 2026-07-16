# KenshiRing - KenshiLib Plugins

A mod that adds new sections and various buffs and debuffs.

Inspired by the ["Extra Inventory Sections"](https://www.nexusmods.com/kenshi/mods/1838) mod, this is a fork of it, featuring a complete overhaul. With the addition of effects for clothing items

Thanks to [BFrizzleFoShizzle](https://github.com/BFrizzleFoShizzle) for the opportunity to create mods like this.
Thanks to [Genpretz](https://github.com/Genpretz). Using his project with the new sections, I created my own.

### Usage Requirements
  1. [RE_Kenshi v0.3.4 or Later](https://www.nexusmods.com/kenshi/mods/847)

### Description

15 new inventory sections added.

Redesigned character clothing generation that allows filling all inventory slots if suitable clothing is available in the list.

<details>
  <summary>Inventory</summary>
  
  ![img](https://github.com/xprvtt/KenshiRing/blob/main/Documents/Assets%20github/inv.png)

Additional slot for a small knife (ATTACH_WEAPON 3x1) — currently disabled.

Face area, distributed across 3 additional sections ("Extra Inventory Sections") with attachments:
ATTACH_HAT 3x1
ATTACH_EYES 3x1
ATTACH_BELT 3x1

Ears: ATTACH_HAIR 3x1

Neck: ATTACH_NECK 2x2 (Extra Inventory Sections)

Chain: ATTACH_NECK 3x1

Hand: ATTACH_GLOVES 2x2

Hand/Forearm: ATTACH_GLOVES 4x2

Shoulders: ATTACH_BACK 4x3

Hip: ATTACH_LEGS 2x2

Lower leg: ATTACH_BOOTS 2x3

Fingers: ATTACH_BEARD 4x2

Toes: ATTACH_BEARD 4x2

Pocket: ATTACH_NONE 2x4 (for any item)

___

</details>

new clothing for these "ring" slots uses the finger and toe slots

<details>
  <summary>Ring, a small part</summary>
  
  ![img](https://github.com/xprvtt/KenshiRing/blob/main/Documents/Assets%20github/ring.png)

___
  
</details>

items with buffs and debuffs that you can equip to gain their power (currently only rings)

<details>
  <summary>Gif</summary> 
  
![img1](https://github.com/xprvtt/KenshiRing/blob/main/Documents/Assets%20github/amputator.gif)

![img1](https://github.com/xprvtt/KenshiRing/blob/main/Documents/Assets%20github/effect.gif)

___

</details>


<details>
  <summary>Effects 0.0.1</summary>
  
___

<p align="center">aggressiveness</p>
  
#DeathGaze -> OFF

___

<p align="center">Melee attack</p>

#Vampir

#AbsolutePenetration

#DivineStrike

#AreaDamage

#Disarmament

#ArmorStrip

#Amputator

#LimbRipper

___

<p align="center">Melee def</p>

#BladeMail

#DamageNullification

#ClutchSurvival

#UntouchableSoul

___

<p align="center">Eating</p>

#Poisonous

#Paralysis

#IronSkin

#BeastRevival

___

<p align="center">Medic</p>

#DivineHealing

#SoulDeadMedic

#BloodTransfusion

#Bloodsucker

#Nanites

___

<p align="center">Medic patient</p>

#CompliantPatient

#ViolentPatient

#DivineRigging -> OFF

___

<p align="center">Ranger def</p>

#Bulletproof

___

<p align="center">Ranger attack</p>

#SniperShot

#DivineShot

#CharmShot

#ConversionShot

#LifeStealingShot

#Bonebreaker

#SurgeonDream

#PainfulShot

#BloodTollShot

#DemonsShotToll

#ShotWanderingSoul

#KhorneWanderingSoulShot

#AnnihilatingShot

___

</details>

___

<details>
  <summary>FULL DESCRIPTION RUS</summary>

# ближний бой, атака<br/>

#Vampir <br/>
при успешном ударе ближним оружием вы восстановите немного здоровья, но не больше максимального<br/>
свойства <шанс сработать - усиление в %><br/>

#AbsolutePenetration<br/>
добавляет пробитие вашему ближнему оружию к уже имеющемуся<br/>
свойства <шанс сработать - отдельное добавочное пробитие %><br/>

#DivineStrike<br/>
божественный удар дробящий жертву изнутри<br/>
свойства <шанс сработать - % урона от максимального здоровья жертвы><br/>

#AreaDamage<br/>
ваши удары наносятся всем частям тела сразу<br/>
свойства <шанс сработать - % от вашего урона, который нанесется всем частям тела><br/>

#Disarmament<br/>
Ваш удар настолько силен, что силой вырывает оружие противника из рук<br/>
свойства <шанс сработать - количество СЕКЦИЙ из, которого будет выбито оружие><br/>
000 - 049 -> 1<br/>
050 - 099 -> 2<br/>
100 - 149 -> 3<br/>
150 - 199 -> 4<br/>
200 - 255 -> 5<br/>

#ArmorStrip<br/>
Ваш удар настолько силен, что разрывает броню и одежду противника<br/>
свойства <шанс сработать - количество одежды><br/>
000 - 049  -> 1<br/>
050 - 099  -> 2<br/>
100 - 149  -> 3<br/>
150 - 199  -> 4<br/>
200 - 255  -> 5<br/>

#LimbRipper<br/>
ваш становится настолько заточенным, что удары отрубают конечности случайную конечность<br/>
свойства <шанс сработать - шанс отрубить еще одну конечность><br/>
гарантированно отрубает конечность, у того у кого их 4<br/>
если у врага, не все конечности, удар может прийтись на конечность, которая уже отрублена<br/>
100-149 -> +1 попытка отрубить еще одну конечность<br/>
150-199 -> +2 попытка отрубить еще одну конечность<br/>
200-255 -> +3 попытка отрубить еще одну конечность<br/>

#Amputator <br/>
Вы становитесь настолько обезумевшим воином, что одним ударом превращаете врага в салат из конечностей<br/>
свойства <шанс сработать - NONE><br/>

# ближний бой, защита<br/>

#BladeMail<br/>
вы отражаете часть урона во врага в случайную часть тела<br/>
свойства <шанс сработать - % от количества полученного урона><br/>

#DamageNullification<br/>
вы анулируете часть полученного урона<br/>
свойства <шанс сработать - %, на который уменьшится урон><br/>

#ClutchSurvival<br/>
ваши конечности восстанавливаются когда по вам бьют в ближнем бою и в конечном итоге не могут быть повреждены, но вы получаете повышенный урон<br/>
свойства <шанс сработать - %, увеличения урона по вам><br/>

#UntouchableSoul<br/>
когда вас атакуют в ближнем бою, ваша душа вырывается из тела направляясь к противнику и вытесняя его душу из тела противника, теперь вы владелец тела противника, ваше тело оставшись без души умирает<br/>
свойства <шанс сработать - NONE><br/>

# бой с животными<br/>

#Poisonous<br/>
Вы становитесь ядовитым, монстры которые будут вас есть, будут так же получать урон<br/>
свойства <шанс сработать - сила урона><br/>

#Paralysis<br/>
В ваших венах течет яд скорпиона, парализующий монстров которые вас едят на некоторое время, вы получаете повышенный урон от поедания<br/>
свойства <шанс сработать - повышение времени, %><br/>

#IronSkin<br/>
Вы становитесь обладателем железной кожи, вас теперь не так легко съесть<br/>
свойства <шанс сработать - уменьшение урона от поедания, %><br/>

#BeastRevival<br/>
Когда вашу голову доедают, получите второй шанс на жизнь в этом мире, но уже в теле животного, которое вас съело<br/>
свойства <шанс сработать - NONE><br/>

# оказание помощи себе или другим<br/>

#DivineHealing<br/>
Вы обладаете божественной силой, которая позволяет излечить полностью пациента<br/>
свойства <шанс сработать -  шанс сработать><br/>
лечение происходит за каждый тик, поэтому метод используемый игрой применяется очень много раз за секунду<br/>
второй шанс сработать лишь компенсирует, но не гарантирует что лечение применится, хотя шансы все равно остаются большие. 0% означает, что никогда не применится<br/>

#SoulDeadMedic<br/>
Когда вы лечите, вы получаете бонус к своему навыку лечения <br/>
свойства <шанс сработать - дополнительный уровень><br/>

#BloodTransfusion<br/>
Когда вы лечите, вы отдаете свое здоровье, тому, кого лечите в чуть больше объеме<br/>
свойства <шанс сработать - усиление лечения пациента><br/>

#Bloodsucker<br/>
Вы становитесь безумным доктором, который похищает здоровье пациента, восстанавливая его себе, даже сверх максимального здоровья<br/>
свойства <шанс сработать - усиление кражи><br/>

#Nanites<br/>
Ваши вены заполоняют микророботы, которые восстанавливают изношенные роботизированные протезы без ремкровати<br/>
свойства <шанс сработать - усиление восстановления><br/>

# принятие помощи от кого то<br/>

#CompliantPatient<br/>
Вы - послушный пациент, за это вы имеете шанс восстановиться полностью сразу<br/>
свойства <шанс сработать -  шанс сработать><br/>

#ViolentPatient<br/>
Вы - слишком буйный пациент, невзначай вы раните того, кто вам помогает и восстанавливаете здоровье себе гораздо быстрее, даже сверх максимального<br/>
свойства <шанс сработать - усиление восстановления здоровья><br/>

# дальний бой, защита<br/>

#Bulletproof<br/>
Вы становитесь пуленепробиваемым, снаряды щекочат вас, восстанавливаете здоровье, когда по вам попадают<br/>
свойства <шанс сработать - % восстановления здоровья от максимального здоровья><br/>

# дальний бой, атака<br/>

#SniperShot<br/>
Ваши выпущенные снаряды становятся настолько сильными, что наносят огромный урон по случайной части тела дополнительно<br/>
свойства <шанс сработать - % усиления урона от максимального здоровья цели><br/>

#DivineShot<br/>
Ваши выстрелы несут божественный гнев, который наносит урон всем частям тела вне зависимости от брони<br/>
свойства <шанс сработать - % усиления урона от максимального здоровья цели><br/>

#CharmShot<br/>
Ваши снаряды отравлены, и повергают в ступор того, по кому попали<br/>
свойства <шанс сработать - NONE><br/>

#ConversionShot<br/>
Вы становитесь проповедником этого мира, ваши выстрелы обращают противников сражаться на вашей стороне<br/>
свойства <шанс сработать - NONE><br/>

#LifeStealingShot<br/>
Теперь ваши выстрелы крадут здоровье у цели, но не выше максимального<br/>
свойства <шанс сработать - усиление кражи><br/>

#Bonebreaker<br/>
Ваши выстрелы разрывают случайные конечности противника<br/>
свойства <шанс сработать - шанс дополнительно сработать><br/>
100 -> +1<br/>
150 -> +2<br/>
200 -> +3<br/>

#SurgeonDream<br/>
Ваши выстрелы заставляют противника, покинуть сражение, так, как сделал бы это хирург<br/>
свойства <шанс сработать - NONE><br/>

#AnnihilatingShot<br/>
Любое существо по которому вы попадете анигилирует<br/>
свойства <шанс сработать - шанс оставить в живых жертву><br/>

#PainfulShot<br/>
Ваши выстрелы становятся болезненными как для противника так и для вас<br/>
свойства <шанс сработать - увеличение урона по вам><br/>

#BloodTollShot<br/>
За вашу силу приходит час расплаты, при каждом выстреле вы можете потерять ВСЕ конечности<br/>
свойства <шанс сработать - NONE><br/>

#DemonsShotToll<br/>
Вы расплачиваетесь случайной конечностью за ваш выстрел<br/>
свойства <шанс сработать - NONE><br/>

#ShotWanderingSoul<br/>
Ваша душа теперь перемешается в тело противника, по которому попали, но только своей расы, предыдущее ваше тело умирает<br/>
свойства <шанс сработать - NONE><br/>

#KhorneWanderingSoulShot<br/>
В вас теперь находится душа демона, теперь при попадании, ваша душа перемешается в тело противника, любого противника, предыдущее ваше тело умирает<br/>
свойства <шанс сработать - NONE><br/>

</details>

___

<details>
  <summary>FULL DESCRIPTION EN</summary>
  
# melee combat, attack<br/>

#Vampir <br/>
Upon successfully hitting with a melee weapon, you restore some health, but not above the maximum amount<br/>
properties <chance to trigger - strength in %><br/>

#AbsolutePenetration<br/>
Adds armor penetration to your melee weapon in addition to the existing penetration<br/>
properties <chance to trigger - additional separate armor penetration %><br/>

#DivineStrike<br/>
A divine strike that crushes the victim from the inside<br/>
properties <chance to trigger - % of damage from the victim's maximum health><br/>

#AreaDamage<br/>
Your attacks hit all body parts simultaneously<br/>
properties <chance to trigger - % of your damage that will be dealt to all body parts><br/>

#Disarmament<br/>
Your strike is so powerful that it forcefully tears the enemy's weapon from their hands<br/>
properties <chance to trigger - number of SECTIONS from which the weapon will be knocked out><br/>
000 - 049 -> 1<br/>
050 - 099 -> 2<br/>
100 - 149 -> 3<br/>
150 - 199 -> 4<br/>
200 - 255 -> 5<br/>

#ArmorStrip<br/>
Your strike is so powerful that it tears apart the enemy's armor and clothing<br/>
properties <chance to trigger - number of clothing pieces removed><br/>
000 - 049  -> 1<br/>
050 - 099  -> 2<br/>
100 - 149  -> 3<br/>
150 - 199  -> 4<br/>
200 - 255  -> 5<br/>

#LimbRipper<br/>
Your weapon becomes so sharp that your attacks sever random limbs<br/>
properties <chance to trigger - chance to sever an additional limb><br/>
Guaranteed to sever a limb of those who have all 4 limbs<br/>
If the enemy does not have all limbs, the attack may target a limb that has already been severed<br/>
100-149 -> +1 additional limb severing attempt<br/>
150-199 -> +2 additional limb severing attempts<br/>
200-255 -> +3 additional limb severing attempts<br/>

#Amputator <br/>
You become such a crazed warrior that a single strike turns your enemy into a salad of limbs<br/>
properties <chance to trigger - NONE><br/>

# melee combat, defense<br/>

#BladeMail<br/>
You reflect part of the received damage back to the enemy's random body part<br/>
properties <chance to trigger - % of received damage><br/>

#DamageNullification<br/>
You nullify part of the received damage<br/>
properties <chance to trigger - % by which the damage is reduced><br/>

#ClutchSurvival<br/>
Your limbs regenerate when you are hit in melee combat and eventually cannot be damaged, but you receive increased damage<br/>
properties <chance to trigger - % of increased damage taken><br/>

#UntouchableSoul<br/>
When you are attacked in melee combat, your soul leaves your body and moves toward the attacker, forcing their soul out of their body. You become the owner of the enemy's body, while your old body dies without a soul<br/>
properties <chance to trigger - NONE><br/>

# animal combat<br/>

#Poisonous<br/>
You become poisonous. Monsters that eat you will also receive damage<br/>
properties <chance to trigger - damage strength><br/>

#Paralysis<br/>
Scorpion venom flows through your veins, paralyzing monsters that eat you for a period of time. You receive increased damage from being eaten<br/>
properties <chance to trigger - increased duration, %><br/>

#IronSkin<br/>
You gain iron skin, making you much harder to eat<br/>
properties <chance to trigger - reduction of eating damage, %><br/>

#BeastRevival<br/>
When your head is fully eaten, you receive a second chance at life in this world, but now inside the body of the animal that ate you<br/>
properties <chance to trigger - NONE><br/>

# healing yourself or others<br/>

#DivineHealing<br/>
You possess divine power that allows you to completely heal a patient<br/>
properties <chance to trigger - activation chance><br/>
Healing occurs every tick, so the method used by the game is called many times per second<br/>
The second activation chance only compensates for it and does not guarantee that the healing will be applied, although the chances remain high. 0% means it will never activate<br/>

#SoulDeadMedic<br/>
When you heal, you receive a bonus to your healing skill<br/>
properties <chance to trigger - additional level><br/>

#BloodTransfusion<br/>
When you heal, you give your own health to the person being healed in a slightly larger amount<br/>
properties <chance to trigger - healing amplification for the patient><br/>

#Bloodsucker<br/>
You become a mad doctor who steals the patient's health, restoring it to yourself, even beyond maximum health<br/>
properties <chance to trigger - stealing amplification><br/>

#Nanites<br/>
Your veins become filled with microrobots that repair worn robotic prosthetics without a repair bed<br/>
properties <chance to trigger - regeneration amplification><br/>

# receiving help from someone<br/>

#CompliantPatient<br/>
You are a compliant patient. Because of this, you have a chance to recover completely instantly<br/>
properties <chance to trigger - activation chance><br/>

#ViolentPatient<br/>
You are an overly violent patient. You accidentally injure the person helping you and restore your own health much faster, even beyond maximum health<br/>
properties <chance to trigger - health restoration amplification><br/>

# ranged combat, defense<br/>

#Bulletproof<br/>
You become bulletproof. Projectiles only tickle you, and you restore health when hit<br/>
properties <chance to trigger - % of maximum health restored><br/>

# ranged combat, attack<br/>

#SniperShot<br/>
Your fired projectiles become so powerful that they deal massive additional damage to a random body part<br/>
properties <chance to trigger - % of damage amplification from the target's maximum health><br/>

#DivineShot<br/>
Your shots carry divine wrath, dealing damage to all body parts regardless of armor<br/>
properties <chance to trigger - % of damage amplification from the target's maximum health><br/>

#CharmShot<br/>
Your projectiles are poisoned and leave the target stunned after being hit<br/>
properties <chance to trigger - NONE><br/>

#ConversionShot<br/>
You become a preacher of this world. Your shots convert enemies to fight on your side<br/>
properties <chance to trigger - NONE><br/>

#LifeStealingShot<br/>
Your shots now steal health from the target, but not above maximum health<br/>
properties <chance to trigger - stealing amplification><br/>

#Bonebreaker<br/>
Your shots tear apart random enemy limbs<br/>
properties <chance to trigger - additional activation chance><br/>
100 -> +1<br/>
150 -> +2<br/>
200 -> +3<br/>

#SurgeonDream<br/>
Your shots force enemies to leave the battle, just as a surgeon would do<br/>
properties <chance to trigger - NONE><br/>

#AnnihilatingShot<br/>
Any creature you hit is annihilated<br/>
properties <chance to trigger - chance to leave the victim alive><br/>

#PainfulShot<br/>
Your shots become painful both for the enemy and yourself<br/>
properties <chance to trigger - increase in damage taken><br/>

#BloodTollShot<br/>
Your power comes with a price. With every shot, you may lose ALL limbs<br/>
properties <chance to trigger - NONE><br/>

#DemonsShotToll<br/>
You pay for your shot with a random limb<br/>
properties <chance to trigger - NONE><br/>

#ShotWanderingSoul<br/>
Your soul now moves into the body of the enemy you hit, but only if they are of your own race. Your previous body dies<br/>
properties <chance to trigger - NONE><br/>

#KhorneWanderingSoulShot<br/>
A demon's soul now resides within you. When you hit an enemy, your soul moves into their body, regardless of their race. Your previous body dies<br/>
properties <chance to trigger - NONE><br/>

</details>

___


### Сompatibility
  1. Fully compatible with mods that used "Extra Inventory Sections"
  2. Incompatible with "Extra Inventory Section" and any other mods that modify inventory sections.
  3. Incompatible with mods that alter character clothing generation.
     
### compatibility questions (unverified)
  1. The mod uses its own hooks for in-game effects—specifically for melee and ranged attacks, when an animal or monster is eating you, and when you are healing someone.

If you notice any incompatibility in these areas, please let me know.



### disclaimer

This project is not affiliated with or supported by Lo-Fi Games. Kenshi is the property of its respective rights holders.

The program is provided "as is". Ring icons generated by AI.

# Compilation
### Requirements
[KenshiLib 0.4.0 or Later](https://github.com/BFrizzleFoShizzle/RE_Kenshi)

### Preparation
1. [Perform all preparatory actions](https://github.com/weisspure/re_kenshi-working-solution/blob/main/README.md)
2. Change the output file directory
<details>
  <summary>Image</summary> 
  
  ![img](https://github.com/xprvtt/KenshiRing/blob/main/Documents/Assets%20github/property%20mvs.png)
</details>

3. Build the project.
5. To understand how it works, go to the [Documents](https://github.com/xprvtt/KenshiRing/tree/main/Documents) folder, the project's visual implementation is presented there.
