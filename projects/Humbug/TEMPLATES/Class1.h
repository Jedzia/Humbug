$START$xxx
#ifndef $Filename:uc$_H
#define $Filename:uc$_H


class $Filename$ {
public:

    $Filename$();
    ~$Filename$();

    const char *language(int x) const;
	/*Vorher*/$#IF(1)$ char test=$Filename$; Du $Filename:lc$ Filename $Filename$ $Filename$ older $Depp$ $#ENDIF$//Nachher
// Und anders:
    /*Vorher*/$#IF(0)$char test="Du older $Filename$"$#ENDIF$//Nachher
$#IF(0)$/*VorherGeil*/string test="Du older $Filename$" //Nachher $Filename$ Toll was?$#ENDIF$
$#IF(1)$
  std::string older("$Filename$-$Filename$");
$#ENDIF$
private:
	int i;
};

#endif // $Filename:uc$_H

$END$