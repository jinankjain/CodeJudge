# -*- coding: utf-8 -*-
from __future__ import unicode_literals

from django.db import models, migrations


class Migration(migrations.Migration):

    dependencies = [
        ('judge', '0011_auto_20160330_1510'),
    ]

    operations = [
        migrations.RemoveField(
            model_name='problem',
            name='contest',
        ),
        migrations.AddField(
            model_name='problem',
            name='contest',
            field=models.ManyToManyField(to='judge.Contest'),
        ),
    ]
