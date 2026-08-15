# Strategy

## Real-life example

A navigation app can use a driving, walking, or cycling route algorithm chosen by the user.

## Explain it like I'm in kindergarten

To make a list, choose the “star list” helper or the “HTML list” helper. Both make lists, but their writing looks different.

## The code that really matters

`22_Strategy_or_Policy/01_DynamicStrategy.cpp`

```cpp
unique_ptr<ListStrategy> list_strategy;
list_strategy = make_unique<HtmlListStrategy>();
list_strategy->add_list_item(os, item);
```

`TextProcessor` holds one interchangeable `ListStrategy` and delegates formatting to it. `set_output_format()` selects the algorithm at runtime.

## What to remember

- Encapsulate interchangeable algorithms behind one interface.
- The client chooses which algorithm to use.
- Policies are often compile-time strategies; this example is dynamic.
