project('GTK Sample App', ['c'],
        version: '1.0.0',
	license : 'GPL')

add_project_arguments('-rdynamic', language: 'c')

gtk = dependency('gtk+-3.0')

src = ['src/main.c',
       'src/app.c',
       'src/callbacks.c']

executable('gtk-sample-app', src, dependencies : gtk)
