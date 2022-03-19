readline()은 프롬프트를 출력하고 사용자에게 한줄의 텍스트를 읽고 반환한다.
프롬프트가 NULL, 빈문자열이면 프롬프트가 표시되지 않는다.
readline이 반환하는 줄은 malloc으로 할당된다. 호출자는 free를 해주어야 한다.

반환된 한 줄은 마지막 개행이 제거된 채이다. 즉, 텍스트만 남는다.

If readline encounters an EOF while reading the line, and the line is empty at that point, then (char *)NULL is returned. Otherwise, the line is ended just as if a newline had been typed.
만약 readline이 줄에서 EOF를 만났고, 그때 그 줄이 그 시점에 비었다면,
NULL이 반환된다.
그 외에는, 줄이

readline은 그것이 화면에 표시되기 전에 프롬프트에 대한 확장기능을 제공한다.
자세한 내용은 2.4.6 참고할것.
특히 프롬프트가 표시되지않는 문자(\n,\t등)를 포함할경우에는 더욱!