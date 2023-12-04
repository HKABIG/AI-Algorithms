contains(refrigerator, [milk, eggs, cheese, vegetables, fruits]).
temperature_range(freezer, -18, -12).
temperature_range(main_compartment, 2, 4).
temperature_range(vegetable_drawer, 5, 8).

freezing_item(ice_cream).
freezing_item(frozen_meat).
freezing_item(frozen_vegetables).
should_store_in_freezer(Item):-freezing_item(Item).

should_store_in_vegetable_drawer(Item):-perishable_item(Item).
perishable_item(vegetables).
perishable_item(fruits).

is_in_refrigerator(Item):-contains(refrigerator, Contents),member(Item, Contents).

is_in_freezer(Item):-temperature_range(freezer, _, MAX_TEMP),freezing_item(Item),should_store_in_freezer(Item),current_temperature(Item, Temp),Temp =< MAX_TEMP.

is_in_vegetable_drawer(Item):-temperature_range(vegetable_drawer, MinTemp, _),perishable_item(Item),should_store_in_vegetable_drawer(Item),current_temperature(Item, Temp), Temp =< MinTemp.

compartment_containing(Item, Compartment):-should_store_in_freezer(Item),Compartment = freezer.
compartment_containing(Item, Compartment):-should_store_in_vegetable_drawer(Item),Compartment = vegetable_drawer.
compartment_containing(_, Compartment):-Compartment = main_compartment.
current_temperature(Item, Temp):-compartment_containing(Item, Compartment),temperature_range(Compartment, MinTemp, MaxTemp),random_between(MinTemp, MaxTemp, Temp).

specify_temperature(Item, MIN_TEMP, MAX_TEMP):-compartment_containing(Item, Compartment),temperature_range(Compartment, MIN_TEMP, MAX_TEMP).
