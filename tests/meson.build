hello_window = executable('hello_window', 'hello_window.cpp', dependencies: [wrapgl_dep])
hello_triangle = executable('hello_triangle', 'hello_triangle.cpp', dependencies: [wrapgl_dep])
hello_orange = executable('hello_orange', 'hello_orange.cpp', dependencies: [wrapgl_dep, glad_dep])
hello_polygon = executable('hello_polygon', 'hello_polygon.cpp', dependencies: [wrapgl_dep, glad_dep])

test('hello_window', hello_window, timeout: 0)
test('hello_triangle', hello_triangle, timeout: 0)
test('hello_orange', hello_orange, timeout: 0)
test('hello_polygon', hello_polygon, timeout: 0)
