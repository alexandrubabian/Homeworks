Babian Stelian Alexandru 312CD
Tema 2- Metode Numerice
In spatele unui motor de cautare

Cerinta 1-Iterative
	Intrucat am avut doar 2 exemple pentru care sa rulam codul, sper ca am acoperit toate
cazurile care pot aparea. Am creat matricea de adiacenta din citire si dupa am eliberat orice
valoare de 1 de pe diagonala principala. Intrucat algoritmul ni s-a dat de pe Wikipedia, tot ce
am avut de rezolvat a fost sa aplicam algoritmul cat timp diferenta dintre matricea R anterioara
si matricea R prezenta,in modul, este mai mica decat eroarea data ca parametru.
	Pentru matricea K am folosit functia inversa intrucat K este oricum o matrice diagonala
si nu va afecta timpul de executie folosirea functiei inv.

Cerinta 2-Algebraic
	Crearea matricei de adiacenta este exact la fel, ce este diferit in algoritmul Algebraic
este faptul ca trebuie sa aplicam GranSchmidt pe matricea (I-d*M), unde I este matricea unitate
, d este dat ca parametru iar M = (K * A)', unde K este este inversa matricei care are pe diagonala
pentru fiecare linie in parte din A, suma elementelor. Cum GramSchmidt genereaza 2 matrici, una 
ortogonala, Q si una superior triunghiulara, R, dar tinand cont ca variabila este cea returnata
de functia Algebraic, am numit aceasta matrice Z. De la linia 40 pana la final este codul 
prezentat pe Wikipedia. Functiile SST si GramSchmidt sunt cele invatate la laborator.

Cerinta 3-PageRank
De data aceasta am facut o citire "superficiala" pana la cele 2 valori de la final, va1,val2.
Am stocat valorile R1 si R2 rezultate din apelarea functiilor anterioare, Iterative si Algebraic,
am sortat vectorul R2 si am verificat pt fiecare element din vectorul sortat cu functia apartenenta,
care se foloseste de conditiile de continuitate.

Consider ca a fost o tema interesanta, care a apelat la informatii noi si informatii acumulate de la
laborator.
