
### C++11 range-based цикл
https://ru.stackoverflow.com/questions/678863/c11-range-based-%D1%86%D0%B8%D0%BA%D0%BB/678865

    const auto& если объект не будет меняться в теле цикла и/или оптимизация операций копирования.
    auto& если необходимо изменить объект в коллекции.
    auto если объект будет изменяться, но его копия в коллекции должна остаться неизменной.
