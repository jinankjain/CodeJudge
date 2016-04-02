# -*- coding: utf-8 -*-
from __future__ import unicode_literals

from django.db import models, migrations
import ckeditor.fields
import django.utils.timezone
from django.conf import settings
import django.core.validators


class Migration(migrations.Migration):

    dependencies = [
        ('auth', '0001_initial'),
    ]

    operations = [
        migrations.CreateModel(
            name='Hacker',
            fields=[
                ('id', models.AutoField(verbose_name='ID', serialize=False, auto_created=True, primary_key=True)),
                ('password', models.CharField(max_length=128, verbose_name='password')),
                ('last_login', models.DateTimeField(default=django.utils.timezone.now, verbose_name='last login')),
                ('is_superuser', models.BooleanField(default=False, help_text='Designates that this user has all permissions without explicitly assigning them.', verbose_name='superuser status')),
                ('username', models.CharField(unique=True, max_length=20, validators=[django.core.validators.RegexValidator(b'^[0-9a-zA-Z]*$', message=b'Only alphanumeric characters are allowed.')])),
                ('email', models.EmailField(unique=True, max_length=255, verbose_name=b'email address')),
                ('first_name', models.CharField(max_length=30, null=True, blank=True)),
                ('last_name', models.CharField(max_length=50, null=True, blank=True)),
                ('date_joined', models.DateTimeField(auto_now_add=True)),
                ('is_active', models.BooleanField(default=True)),
                ('is_staff', models.BooleanField(default=False)),
                ('profileImage', models.ImageField(upload_to=b'avatar')),
                ('groups', models.ManyToManyField(related_query_name='user', related_name='user_set', to='auth.Group', blank=True, help_text='The groups this user belongs to. A user will get all permissions granted to each of his/her group.', verbose_name='groups')),
                ('user_permissions', models.ManyToManyField(related_query_name='user', related_name='user_set', to='auth.Permission', blank=True, help_text='Specific permissions for this user.', verbose_name='user permissions')),
            ],
            options={
                'abstract': False,
            },
            bases=(models.Model,),
        ),
        migrations.CreateModel(
            name='Comments',
            fields=[
                ('id', models.AutoField(verbose_name='ID', serialize=False, auto_created=True, primary_key=True)),
                ('commentText', models.TextField()),
            ],
            options={
            },
            bases=(models.Model,),
        ),
        migrations.CreateModel(
            name='Contest',
            fields=[
                ('id', models.AutoField(verbose_name='ID', serialize=False, auto_created=True, primary_key=True)),
                ('contestName', models.CharField(unique=True, max_length=200)),
                ('startTime', models.DateTimeField()),
                ('endTime', models.DateTimeField()),
            ],
            options={
            },
            bases=(models.Model,),
        ),
        migrations.CreateModel(
            name='Language',
            fields=[
                ('id', models.AutoField(verbose_name='ID', serialize=False, auto_created=True, primary_key=True)),
                ('language', models.CharField(max_length=200)),
                ('extension', models.CharField(max_length=10)),
            ],
            options={
            },
            bases=(models.Model,),
        ),
        migrations.CreateModel(
            name='Problem',
            fields=[
                ('id', models.AutoField(verbose_name='ID', serialize=False, auto_created=True, primary_key=True)),
                ('problemSetter', models.CharField(max_length=200)),
                ('problemTitle', models.CharField(max_length=200)),
                ('problemStatement', ckeditor.fields.RichTextField()),
                ('testInput', models.FileField(upload_to=b'testInput')),
                ('testOutput', models.FileField(upload_to=b'testOutput')),
                ('timeLimit', models.PositiveSmallIntegerField()),
                ('languagesAllowed', models.CommaSeparatedIntegerField(max_length=200)),
                ('inputFormat', ckeditor.fields.RichTextField()),
                ('outputFormat', ckeditor.fields.RichTextField()),
                ('constraints', ckeditor.fields.RichTextField()),
                ('sampleInput', ckeditor.fields.RichTextField()),
                ('sampleOutput', ckeditor.fields.RichTextField()),
                ('solvedBy', models.PositiveSmallIntegerField(default=0)),
                ('contest', models.ForeignKey(to='judge.Contest')),
            ],
            options={
            },
            bases=(models.Model,),
        ),
        migrations.CreateModel(
            name='Solution',
            fields=[
                ('id', models.AutoField(verbose_name='ID', serialize=False, auto_created=True, primary_key=True)),
                ('solution', models.FileField(upload_to=b'solution')),
                ('attempts', models.PositiveSmallIntegerField()),
                ('time', models.DecimalField(max_digits=2, decimal_places=2)),
                ('status', models.PositiveSmallIntegerField()),
                ('contest', models.ForeignKey(to='judge.Contest')),
                ('hacker', models.ForeignKey(to=settings.AUTH_USER_MODEL)),
                ('language', models.ForeignKey(to='judge.Language')),
                ('problem', models.ForeignKey(to='judge.Problem')),
            ],
            options={
            },
            bases=(models.Model,),
        ),
        migrations.AddField(
            model_name='comments',
            name='contest',
            field=models.ForeignKey(to='judge.Contest'),
            preserve_default=True,
        ),
        migrations.AddField(
            model_name='comments',
            name='hacker',
            field=models.ForeignKey(to=settings.AUTH_USER_MODEL),
            preserve_default=True,
        ),
        migrations.AddField(
            model_name='comments',
            name='problem',
            field=models.ForeignKey(to='judge.Problem'),
            preserve_default=True,
        ),
    ]
