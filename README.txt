Kompileerimine: g++ prim.cpp -o prim
Graafis olevad servad loetakse failist servad.txt
servad.txt peab olemas samas kaustas, kus ly13.exe
Graafi toespuu tekitatakse faili toespuu.txt
Graafi toespuu leidmiseks on kasutatud Primi alogritmi.

Servad peavad olema failist kujutatud formaadis: algustipp lõpptipp kaal
Näiteks:
1 2 50
1 3 30

Primi alogritmi kirjeldus
Primi algoritm alustab tööd juurtipust, milleks on 1.
Leiab sellest väljuvad servad ja võtab töösse väikseima kaaluga serva.
Kontrollitakse, et serva tipud poleks juba lisatud tippude hulgas, kui 
on, siis leiab uue väikseima kaaluga serva.
Leitud serv lisatakse minimaalsega kaaluga toespuusse.
Töödeldava serva lõpptipust väljuvad servad lisatakse väikseima kaaluga servade järjekorda.
Protsess kestab seni, kuni servade eelistusjärjekord on tühjaks saanud.